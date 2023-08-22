#include <toolchain.h>
#include <linker/sections.h>
#include <arch/cpu.h>
#include "../../core/boot.h"
#include "../../core/macro_priv.inc"
#include "include/mm.h"

.section ".text"

.globl rpi_memzero
rpi_memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt rpi_memzero
	ret

.globl _rpi_start
_rpi_start:
	b master_debug		


master_debug:
	mov x9, lr
	adr	x0, __bss_start
	adr	x1, __bss_end
	sub	x1, x1, x0
	bl 	rpi_memzero

	msr	SPSel, #1
	ldr x3, =(earlyprint_stack + PRINTK_STACK_SIZE) 
	mov	sp, x3

	bl	tpl_main
	br x9
	bl _debug_loop

	eret



_debug_loop:
	mov x10, #0xffff
	mov x11, #0xeeee

	bl safe_print_debug

	b _debug_loop

	b 	proc_hang		// should never come here


proc_hang: 
	b 	proc_hang
	