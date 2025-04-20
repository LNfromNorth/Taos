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
    .globl stack_bottom
stack_bottom:
    .space 4096
    .globl stack_top
stack_top:
