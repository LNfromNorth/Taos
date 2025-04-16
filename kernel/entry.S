.section .text.entry
.globl _start

_start:
    /* setup stack */
    la  sp, stack_top
    call main
halt:
    j halt

.section .bss.stack
.align 4
stack_top:
.space 4096
.global stack_top