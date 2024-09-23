    .section .text.entry
    .globl _start
_start:
    /* setup stack */
    la  sp, stack_top
    call main
halt:
    j halt

    .section .bss.stack
    .align 12
    .global stack_top
stack_top:
    .space 1024 * 4 * 4
    .global stack_top