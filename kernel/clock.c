#include "stdint.h"
#include "printk.h"
#include "riscv.h"
#include "sbi.h"

// test time 1s
uint64_t TIMECLOCK = 10000000;

uint64_t get_cycles() {
    // uint64_t mtime;
    // asm volatile("rdtime %0" :"-r" (mtime): : "memory");
    return csr_read(time);
}

void clock_set_next_event() {
    printk("[DEBUG] set new clock event\n");
    uint64_t next = get_cycles() + TIMECLOCK;
    printk("[DEBUG] next time is %x\n", next);
    sbi_set_timer(next); 
}