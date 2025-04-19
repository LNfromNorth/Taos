.section .text.entry
.globl _start

_start:
    /* setup stack */
    la  sp, stack
    call main
halt:
    j halt
