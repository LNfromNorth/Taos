#include "clock.h"
#include "printk.h"
#include "riscv.h"

void ktrapvec();

void timer_intr();

void trap_init() {
    csr_write(stvec, (uint64_t)ktrapvec);
    printk("[INIT] finish trap init\n");
}

void trap_on() {
    csr_write(sie, (csr_read(sie) | SIE_STIE));
    csr_write(sstatus, (csr_read(sstatus) | SSTATUS_SIE));
    timer_intr();
    printk("[INIT] finish trap on\n");
}

void utrap_handler() {}

void ktrap_handler() {
    uint64_t scause = csr_read(scause);
    // uint64_t sepc = csr_read(sepc);
    if (scause == 0x8000000000000005) { // timer interrupt
        timer_intr();
        printk("[DEBUG] Into a ktrap handler\n");
    }
}

void timer_intr() {
    // now set default function to set next event
    clock_set_next_event();
}
