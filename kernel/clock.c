#include "printk.h"
#include "riscv.h"
#include "sbi.h"
#include "stdint.h"

// test time 1s
uint64_t TIMECLOCK = 10000000;

uint64_t get_cycles() {
    // uint64_t mtime;
    // asm volatile("rdtime %0" :"-r" (mtime): : "memory");
    return csr_read(time);
}

void clock_set_next_event() {
    uint64_t next = get_cycles() + TIMECLOCK;
    sbi_set_timer(next);
}
