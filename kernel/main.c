#include "sbi.h"
#include "sbi_ecall_interface.h"

#define SBI_PUTCHAR(__a0) SBI_ECALL_1(SBI_EXT_0_1_CONSOLE_PUTCHAR, __a0)

void main() {
    SBI_PUTCHAR('H');
    SBI_PUTCHAR('e');
    SBI_PUTCHAR('l');
    SBI_PUTCHAR('l');
    SBI_PUTCHAR('o');
    SBI_PUTCHAR(' ');
    SBI_PUTCHAR('W');
    SBI_PUTCHAR('o');
    SBI_PUTCHAR('r');
    SBI_PUTCHAR('l');
    SBI_PUTCHAR('d');
    SBI_PUTCHAR('!');
    while(1);
}