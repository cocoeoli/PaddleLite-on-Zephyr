#include <toolchain.h>
#include <linker/sections.h>
#include <arch/cpu.h>
#include "../../core/boot.h"
#include "../../core/macro_priv.inc"
#include "include/mm.h"
#include "include/arm/sysregs.h"
#include "include/arm/mmu.h"

#include <devicetree.h>

#include <linker/linker-defs.h>
#include <linker/linker-tool.h>

/////////////////////////////
#define MAIR(attr, mt)	((attr) << ((mt) * 8))

/*
 * TCR flags.
 */

#define TCR_IRGN0_SHIFT		8
#define TCR_IRGN0_MASK		(UL(3) << TCR_IRGN0_SHIFT)
#define TCR_IRGN0_NC		(UL(0) << TCR_IRGN0_SHIFT)
#define TCR_IRGN0_WBWA		(UL(1) << TCR_IRGN0_SHIFT)
#define TCR_IRGN0_WT		(UL(2) << TCR_IRGN0_SHIFT)
#define TCR_IRGN0_WBnWA		(UL(3) << TCR_IRGN0_SHIFT)

#define TCR_IRGN1_SHIFT		24
#define TCR_IRGN1_MASK		(UL(3) << TCR_IRGN1_SHIFT)
#define TCR_IRGN1_NC		(UL(0) << TCR_IRGN1_SHIFT)
#define TCR_IRGN1_WBWA		(UL(1) << TCR_IRGN1_SHIFT)
#define TCR_IRGN1_WT		(UL(2) << TCR_IRGN1_SHIFT)
#define TCR_IRGN1_WBnWA		(UL(3) << TCR_IRGN1_SHIFT)

#define TCR_IRGN_WBnWA		(TCR_IRGN0_WBnWA | TCR_IRGN1_WBnWA)


#define TCR_ORGN0_SHIFT		10
#define TCR_ORGN0_MASK		(UL(3) << TCR_ORGN0_SHIFT)
#define TCR_ORGN0_NC		(UL(0) << TCR_ORGN0_SHIFT)
#define TCR_ORGN0_WBWA		(UL(1) << TCR_ORGN0_SHIFT)
#define TCR_ORGN0_WT		(UL(2) << TCR_ORGN0_SHIFT)
#define TCR_ORGN0_WBnWA		(UL(3) << TCR_ORGN0_SHIFT)

#define TCR_ORGN1_SHIFT		26
#define TCR_ORGN1_MASK		(UL(3) << TCR_ORGN1_SHIFT)
#define TCR_ORGN1_NC		(UL(0) << TCR_ORGN1_SHIFT)
#define TCR_ORGN1_WBWA		(UL(1) << TCR_ORGN1_SHIFT)
#define TCR_ORGN1_WT		(UL(2) << TCR_ORGN1_SHIFT)
#define TCR_ORGN1_WBnWA		(UL(3) << TCR_ORGN1_SHIFT)

#define TCR_ORGN_WBnWA		(TCR_ORGN0_WBnWA | TCR_ORGN1_WBnWA)



#define TCR_T0SZ_OFFSET		0
#define TCR_T1SZ_OFFSET		16
#define TCR_TxSZ(x)		(TCR_T0SZ(x) | TCR_T1SZ(x))
#define TCR_TxSZ_WIDTH		6
#define TCR_T0SZ_MASK		(((UL(1) << TCR_TxSZ_WIDTH) - 1) << TCR_T0SZ_OFFSET)


#define TCR_TG0_SHIFT		14
#define TCR_TG0_MASK		(UL(3) << TCR_TG0_SHIFT)

#define TCR_TG1_SHIFT		30
#define TCR_TG1_MASK		(UL(3) << TCR_TG1_SHIFT)
#define TCR_TG1_16K		(UL(1) << TCR_TG1_SHIFT)
#define TCR_TG1_64K		(UL(3) << TCR_TG1_SHIFT)

#ifdef CONFIG_ARM64_64K_PAGES
#define TCR_TG_FLAGS	TCR_TG0_64K | TCR_TG1_64K
#elif defined(CONFIG_ARM64_16K_PAGES)
#define TCR_TG_FLAGS	TCR_TG0_16K | TCR_TG1_16K
#else /* CONFIG_ARM64_4K_PAGES */
#define TCR_TG_FLAGS	 TCR_TG1_4K
#endif

#ifdef CONFIG_RANDOMIZE_BASE
#define TCR_KASLR_FLAGS	TCR_NFD1
#else
#define TCR_KASLR_FLAGS	0
#endif


#define TCR_SH0_SHIFT		12
#define TCR_SH0_MASK		(UL(3) << TCR_SH0_SHIFT)
#define TCR_SH0_INNER		(UL(3) << TCR_SH0_SHIFT)

#define TCR_SH1_SHIFT		28
#define TCR_SH1_MASK		(UL(3) << TCR_SH1_SHIFT)
#define TCR_SH1_INNER		(UL(3) << TCR_SH1_SHIFT)
#define TCR_SHARED		(TCR_SH0_INNER | TCR_SH1_INNER)
#define TCR_SMP_FLAGS	TCR_SHARED

/* PTWs cacheable, inner/outer WBWA */
#define TCR_CACHE_FLAGS	TCR_IRGN_WBWA | TCR_ORGN_WBWA

#ifdef CONFIG_KASAN_SW_TAGS
#define TCR_KASAN_FLAGS TCR_TBI1
#else
#define TCR_KASAN_FLAGS 0
#endif

#define MAIR(attr, mt)	((attr) << ((mt) * 8))


#define TCR_IPS_SHIFT		32
#define TCR_IPS_MASK		(UL(7) << TCR_IPS_SHIFT)
#define TCR_A1			(UL(1) << 22)
#define TCR_ASID16		(UL(1) << 36)
#define TCR_TBI0		(UL(1) << 37)
#define TCR_TBI1		(UL(1) << 38)
#define TCR_HA			(UL(1) << 39)
#define TCR_HD			(UL(1) << 40)
#define TCR_NFD1		(UL(1) << 54)

#define VA_BITS             39

///////////////////////////

.section ".text"


.global __cpu_setup
__cpu_setup:
	tlbi	vmalle1				// Invalidate local TLB
	dsb	nsh

	mov	x0, #3 << 20
	msr	cpacr_el1, x0			// Enable FP/ASIMD
	mov	x0, #1 << 12			// Reset mdscr_el1 and disable
	msr	mdscr_el1, x0			// access to the DCC from EL0
	isb					// Unmask debug exceptions now,
	msr	daifclr, #8				// since this is per-cpu
//	reset_pmuserenr_el0 x0			// Disable PMU access from EL0
	mrs	x0, id_aa64dfr0_el1
	sbfx	x0, x0, #8, #4
	cmp	x0, #1
	b.lt  9999f
	msr	pmuserenr_el0, xzr

9999:

	ldr	x5, =MAIR(0x00, 0b000) | \
		     MAIR(0x04, 0b001) | \
		     MAIR(0x0c, 0b010) | \
		     MAIR(0x44, 0b011) | \
		     MAIR(0xff, 0b100) | \
		     MAIR(0xbb, 0b101)
	msr	mair_el1, x5
	/*
	 * Prepare SCTLR
	 */
	mov_imm	x0, SCTLR_EL1_SET
	/*
	 * Set/prepare TCR and TTBR. We use 512GB (39-bit) address range for
	 * both user and kernel.
	 */
	ldr	x10, =0x30B5593519
	//ldr x0, [x12]
	//tcr_set_idmap_t0sz	x10, x9
	ldr_l	x9, 25
	bfi	x10, x9, #TCR_T0SZ_OFFSET, #TCR_TxSZ_WIDTH


	/*
	 * Set the IPS bits in TCR_EL1.
	 */
	//tcr_compute_pa_size x10, #TCR_IPS_SHIFT, x5, x6
	mrs	x5, ID_AA64MMFR0_EL1
	// Narrow PARange to fit the PS field in TCR_ELx
	ubfx	x5, x5, #0, #3
	mov	x6, #0x5
	cmp	x5, x6
	csel	x5, x6, x5, hi
	bfi	x10, x5, #32, #3

	msr	tcr_el1, x10

	ret					// return to head.S

.globl _rpi_start
_rpi_start:

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
	b	98f

primary_core:
	/* advertise ourself */
	str	x1, [x0, #BOOT_PARAM_MPID_OFFSET]
#endif
	/* load primary stack and entry point */
	ldr	x24, =(z_interrupt_stacks + CONFIG_ISR_STACK_SIZE)
	ldr	x25, =z_arm64_prep_c

98:
	dmb sy
	mov x1, #0x20

	add	x1, x1, x0
	__dcache_line_size x2, x3
	sub	x3, x2, #1
	tst	x1, x3				// end cache line aligned?
	bic	x1, x1, x3
	b.eq	1f
	dc	civac, x1			// clean & invalidate D / U line
1:	tst	x0, x3				// start cache line aligned?
	bic	x0, x0, x3
	b.eq	2f
	dc	civac, x0			// clean & invalidate D / U line
	b	3f
2:	dc	ivac, x0			// invalidate D / U line
3:	add	x0, x0, x2
	cmp	x0, x1
	b.lo	2b
	dsb	sy

/* el2_set_up *****************/
	msr	SPsel, #1			// We want to use SP_EL{1,2}
	mrs	x0, CurrentEL
	cmp	x0, #0x8
	b.eq	97f

97:
	mov_imm	x0, (SCTLR_EL2_RES1 | ENDIAN_SET_EL2)
	msr	sctlr_el2, x0
	
	mov x2, #0x01
	mov_imm	x0, (HCR_VHE_FLAGS)
	msr hcr_el2, x0
	isb 
/* timer here */
	msr	cntvoff_el2, xzr		// Clear virtual offset

#if defined(CONFIG_GIC_V3)
	mrs	x0, id_aa64pfr0_el1
	ubfx	x0, x0, #24, #4
	cbz	x0, 93f

	mrs	x0, s3_4_c12_c9_5		 //SYS_ICC_SRE_EL2
	orr	x0, x0, #(1 << 0)	// Set ICC_SRE_EL2.SRE==1
	orr	x0, x0, #(1 << 3)	// Set ICC_SRE_EL2.Enable==1
	msr	s3_4_c12_c9_5, x0
	isb					// Make sure SRE is now set
	mrs	x0, s3_4_c12_c9_5		// Read SRE back,
	tbz	x0, #0, 93f			// and check that it sticks
	msr	s3_4_c12_c11_0, xzr		// Reset ICC_HCR_EL2 to defaults
93:
#endif

	mrs	x0, midr_el1
	mrs	x1, mpidr_el1
	msr	vpidr_el2, x0
	msr	vmpidr_el2, x1

	msr hstr_el2, xzr


/* EL2 debug */
	mrs	x1, id_aa64dfr0_el1		// Check ID_AA64DFR0_EL1 PMUVer
	sbfx	x0, x1, #8, #4
	cmp	x0, #1
	b.lt	4f				// Skip if no PMU present
	mrs	x0, pmcr_el0			// Disable debug access traps
	ubfx	x0, x0, #11, #5			// to EL2 and allow access to
4:
	csel	x3, xzr, x0, lt			// all PMU counters from EL1

	/* Statistical profiling */
	ubfx	x0, x1, #32, #4			// Check ID_AA64DFR0_EL1 PMSVer
	cbz	x0, 96f				// Skip if SPE not present
	cbnz	x2, 6f				// VHE?
	mrs	x4, s3_0_c9_c10_7		// If SPE available at EL2,
	and	x4, x4, #(1 << 4)
	cbnz	x4, 5f				// then permit sampling of physical
	mov	x4, #(1 << 6 | 1 << 4)
	msr	s3_4_c9_c9_0, x4		// addresses and physical counter
5:
	mov	x1, #(0x3 << 12)
	orr	x3, x3, x1			// If we don't have VHE, then
	b	96f				// use EL1&0 translation.
6:						// For VHE, use EL2 translation
	orr	x3, x3, #(1 << 14)		// and disable access from EL1
96:
	msr	mdcr_el2, x3	// Configure debug traps

	/* LORegions */
	
	mrs	x1, id_aa64mmfr1_el1
	ubfx	x0, x1, #16, 4
	cbz	x0, 95f
	//a error occur here if enable it
	msr	s3_0_c12_c4_3, xzr	//lorc_el1
	
95:
	msr	vttbr_el2, xzr

	isb

	/* vhe init end */
	bl __reset_prep_c

	bl tpl_main

	bl __create_test_table


	bl master

	ret


	mov_imm	x0, (SCTLR_EL1_RES1 | 0)
	msr	sctlr_el1, x0

	/* Coprocessor traps. */
	mov	x0, #0x33ff
	msr	cptr_el2, x0			// Disable copro. traps to EL2

	/* SVE register access */
	mrs	x1, id_aa64pfr0_el1
	ubfx	x1, x1, #32, #4
	cbz	x1, 7f
/*
	bic	x0, x0, #(1 << 8)		// Also disable SVE traps
	msr	cptr_el2, x0			// Disable copro. traps to EL2
	isb
	mov	x1, #0x1ff				// SVE: Enable full vector
	msr	s3_4_c1_c2_0, x1			// SYS_ZCR_EL2
*/
	/* Hypervisor stub */
7:	adr_l	x0, _hyp_vector_table
	msr	vbar_el2, x0

	/* spsr */
	mov	x0, #(PSR_F_BIT | PSR_I_BIT | PSR_A_BIT | PSR_D_BIT |\
		      PSR_MODE_EL1h)
	msr	spsr_el2, x0
	adr x0, master
	msr elr_el2, x0
	//msr	elr_el2, lr
	mov	w0, #0xe12		// This CPU booted in EL2

	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0

	bl master

	eret

master:

	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0	

	adr	x0, __bss_start
	adr	x1, __bss_end
	sub	x1, x1, x0
	bl 	memzero

	msr	SPSel, #1
	ldr x3, =__tmp_stack 
	mov	sp, x3

	bl	tpl_main

	bl safe_print_debug

	bl __create_page_tables

	bl safe_print_debug

	mov	x0, #VA_START			
	add	sp, x0, #LOW_MEMORY

	ldr	x0, =(TCR_VALUE)		
	msr	tcr_el1, x0

	ldr	x0, =(MAIR_VALUE)
	msr	mair_el1, x0

	bl safe_print_debug
	mov	x0, #SCTLR_MMU_ENABLED	

	isb			
	msr	sctlr_el1, x0
	isb

	ic	iallu
	dsb	nsh
	isb

	bl safe_print_debug

	b proc_hang

	bl _debug_loop

	//mov_imm	x0, (SPSR_DAIF_MASK)
	//msr	spsr_el3, x0

	mov_imm	x0, (SPSR_DAIF_MASK)
	msr	spsr_el2, x0

	mov_imm	x0, (SPSR_DAIF_MASK)
	msr	spsr_el1, x0

	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0

	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el2, x0	

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0


	ldr x3, =__tmp_stack 
	msr sp_el1, x3

	msr	SPSel, #0
	ldr x3, =__tmp_stack 
	mov	sp, x3

	mrs x10, spsr_el1
	mrs x11, spsr_el2
	bl safe_print_debug

	adr	x0, 99f
	msr	elr_el2, x0

	isb

	eret


99:
	ldr x3, =__tmp_stack 
	mov	sp, x3

	bl safe_print_debug

	b 99b


_debug_loop:

	bl safe_print_debug

	b _debug_loop

	b 	proc_hang		// should never come here

_reset_sys_register:
/* cleat xx register */
	mov x0, xzr
	mov x1, xzr
	mov x2, xzr
	mov x3, xzr
	mov x4, xzr
	mov x5, xzr
	mov x6, xzr
	mov x7, xzr
	mov x8, xzr
	mov x9, xzr
	mov x10, xzr
	mov x11, xzr
	mov x12, xzr
	mov x13, xzr
	mov x14, xzr
	mov x15, xzr
	mov x16, xzr
	mov x17, xzr
	mov x18, xzr
	mov x19, xzr
	mov x20, xzr
	mov x21, xzr
	mov x22, xzr
	mov x23, xzr
	mov x24, xzr
	mov x25, xzr
	mov x26, xzr
	mov x27, xzr
	mov x28, xzr
	mov x29, xzr

	ldr x1, =_vector_table
	msr vbar_el2, x1

	mrs x0, hcr_el2
	orr x0, x0, #(1<<5)
	orr x0, x0, #(1<<4)
	orr x0, x0, #(1<<3)
	msr hcr_el2, x0

	ldr x1, =_vector_table
	msr vbar_el1, x1

	msr DAIFClr, #0x7

	ret


	