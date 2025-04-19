#include "memory.h"
#include "stdint.h"
#include "printk.h"
#include "panic.h"

extern char _ekernel[];

static int32_t mmap[PAGE_NUMS(PHYMEM_SIZE)] = {0};

// -------------------------------
// physical memory alloc and free
// -------------------------------

// default get new pages from end of mmap
void* kalloc() {
    int index;
    for(int i = PAGE_NUMS(PHYMEM_SIZE) - 1; i > 0; i--) {
        if(mmap[i] == 0) {
            index = i;
            break;
        }
    }
    mmap[index] = 1;    // set mmap used
    return (void*)(uint64_t)(PHYMEM_START + (index << 12));
}

void kfree(uint64_t addr) {
    int index = ((addr - PHYMEM_START) & 0xfffff000) >> 12;
    if(mmap[index] == 0) {
        panic("free illgle page");
    }
    mmap[index] = 0;
}

// init mmap, set kernel and sbi space to 1, others to 0
void mmap_init() {
    int used_pages = PAGE_NUMS(((uint64_t)_ekernel - PHYMEM_START));
    int total_pages = PAGE_NUMS(PHYMEM_SIZE);
    int i = 0;
    for(; i < used_pages; i++) {
        mmap[i] = 1;                // set used pages to 1
    }
    for(; i < total_pages; i++) {
        mmap[i] = 0;
    }
}

void memory_init() {
    // set bitmap for memory
    mmap_init();
    printk("[INIT] finish mmap init\n");

}

