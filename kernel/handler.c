#include "printk.h"
#include "riscv.h"
#include "clock.h"

void ktrapvec();

void trap_init() {
    csr_write(stvec, (uint64_t)ktrapvec); 
    printk("[INIT] finish trap init\n");
}

void trap_on() {
    csr_write(sie, (csr_read(sie) | SIE_STIE));
    clock_set_next_event();
    csr_write(sstatus, (csr_read(sstatus) | SSTATUS_SIE));
    printk("[INIT] finish trap on\n");
}

void utrap_handler() {

}

void ktrap_handler() {
    printk("[DEBUG] Into a ktrap handler\n");
    clock_set_next_event();
}

void time_intr() {

}