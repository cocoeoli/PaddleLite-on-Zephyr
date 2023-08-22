/*
 * Copyright (c) 2019 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/toolchain.h>
#include <zephyr/linker/sections.h>
#include <zephyr/arch/arm64/cpu.h>
#include <zephyr/arch/arm64/macro.inc>
#include "../../core/boot.h"
#include "../../core/macro_priv.inc"

_ASM_FILE_PROLOGUE

/*
 * Platform specific pre-C init code
 *
 * Note: - Stack is not yet available
 *       - x23, x24 and x25 must be preserved
 */

WTEXT(z_arm64_el3_plat_prep_c)
SECTION_FUNC(TEXT,z_arm64_el3_plat_prep_c)
	ret

WTEXT(z_arm64_el2_plat_prep_c)
SECTION_FUNC(TEXT,z_arm64_el2_plat_prep_c)
	ret

WTEXT(z_arm64_el1_plat_prep_c)
SECTION_FUNC(TEXT,z_arm64_el1_plat_prep_c)
	ret

/*
 * Set the minimum necessary to safely call C code
 */
GTEXT(__reset_prep_c)
SECTION_SUBSEC_FUNC(TEXT,_reset_section,__reset_prep_c)
	/* return address: x23 */
	mov	x23, x30

	switch_el x0, 3f, 2f, 1f
3:
	/* Reinitialize SCTLR from scratch in EL3 */
	ldr	w0, =(SCTLR_EL3_RES1 | SCTLR_I_BIT | SCTLR_SA_BIT)
	msr	sctlr_el3, x0

	/* Custom plat prep_c init */
	bl	z_arm64_el3_plat_prep_c

	/* Set SP_EL1 */
	msr     sp_el1, x24

	b	out
2:
	/* Disable alignment fault checking */
	mrs	x0, sctlr_el2
	bic	x0, x0, SCTLR_A_BIT
	msr	sctlr_el2, x0

	/* Custom plat prep_c init */
	bl	z_arm64_el2_plat_prep_c

	/* Set SP_EL1 */
	msr     sp_el1, x24

	b	out
1:
	/* Disable alignment fault checking */
	mrs	x0, sctlr_el1
	bic	x0, x0, SCTLR_A_BIT
	msr	sctlr_el1, x0

	/* Custom plat prep_c init */
	bl	z_arm64_el1_plat_prep_c

	/* Set SP_EL1. We cannot use sp_el1 at EL1 */
	msr     SPSel, #1
	mov     sp, x24
out:
	isb
	
	/* Select SP_EL0 */
	msr	SPSel, #0

	/* Initialize stack */
	//mov	sp, x24
	ldr x3, =__tmp_stack 
	mov	sp, x3

	bl safe_print_debug	//2

	ret	x23

/*
 * Reset vector
 *
 * Ran when the system comes out of reset. The processor is in thread mode with
 * privileged level. At this point, neither SP_EL0 nor SP_ELx point to a valid
 * area in SRAM.
 */

GTEXT(__reset)
SECTION_SUBSEC_FUNC(TEXT,_reset_section,__reset)

GTEXT(__start)
SECTION_SUBSEC_FUNC(TEXT,_reset_section,__start)
	
	b _rpi_start

GTEXT(__start_zephyr)
SECTION_SUBSEC_FUNC(TEXT,_reset_section,__start_zephyr)

	msr	DAIFSet, #0xf

#if CONFIG_MP_NUM_CPUS > 1

	ldr	x0, =arm64_cpu_boot_params
	get_cpu_id x1
	ldr	x2, [x0, #BOOT_PARAM_MPID_OFFSET]
	cmp	x2, #-1
	beq	primary_core

	/* loop until our turn comes */
1:	dmb	ld
	ldr	x2, [x0, #BOOT_PARAM_MPID_OFFSET]
	cmp	x1, x2
	bne	1b

	/* we can now load our stack pointer value and move on */
	ldr	x24, [x0, #BOOT_PARAM_SP_OFFSET]
	ldr	x25, =z_arm64_secondary_prep_c
	b	2f

primary_core:
	/* advertise ourself */
	str	x1, [x0, #BOOT_PARAM_MPID_OFFSET]
#endif
	/* load primary stack and entry point */
	ldr	x24, =(z_interrupt_stacks + CONFIG_ISR_STACK_SIZE)
	ldr	x25, =z_arm64_prep_c
2:
	/* Prepare for calling C code */
	bl	__reset_prep_c

	/* Platform hook for highest EL */
	bl	z_arm64_el_highest_init
	//ldr x0, BootromContex 

switch_el:
	switch_el x0, 3f, 2f, 1f
3:
	/* EL3 init */
	bl	z_arm64_el3_init

	/* Get next EL */
	adr	x0, switch_el
	bl	z_arm64_el3_get_next_el
	eret

2:
	
	/* EL2 init */
	bl	z_arm64_el2_init

	/* Move to EL1 with all exceptions masked */
	mov_imm	x0, (SPSR_DAIF_MASK | SPSR_MODE_EL1T)
	msr	spsr_el2, x0

	mov_imm	x0, (SPSR_DAIF_MASK)
	msr	spsr_el1, x0

	adr	x0, 1f
	msr	elr_el2, x0

	mov x10, x0
	mrs x0, elr_el2
	mov x11, x0
	bl safe_print_debug		//xx

	eret

1:
	ldr x3, =__tmp_stack 
	mov	sp, x3

	mov x10, sp
	mov x11, x0
	bl safe_print_debug		//xx

	/* EL1 init */
	bl	z_arm64_el1_init

	/* We want to use SP_ELx from now on */
	msr	SPSel, #1

	/* Enable SError interrupts */
	msr	DAIFClr, #(DAIFCLR_ABT_BIT)
	isb
	//ldr x0, BootromContex

	ret	x25  /* either z_arm64_prep_c or z_arm64_secondary_prep_c */
