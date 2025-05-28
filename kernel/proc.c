#include "proc.h"
#include "panic.h"
#include "printk.h"

struct proc procs[NPROC];

int proc_stack_map(pagetable_t kpagetable) {
    int ret = 0;
    for (int i = 0; i < NPROC; i++) {
        uint64_t pa = (uint64_t)kalloc();
        if (pa == 0)
            panic("proc stack map error: no free pages");
        uint64_t va = KSTACK((int)(i));
        ret += page_map_make(kpagetable, va, pa, PAGE_SIZE, PTE_W | PTE_R);
    }
    return ret;
}

void proc_init() {
    for (int i = 0; i < NPROC; i++) {
        procs[i].state = UNUSED;
        procs[i].kstack = KSTACK((int)(i));
    }
    printk("[INIT] finish proc init\n");
}
