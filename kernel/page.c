#include "stdint.h"
#include "string.h"
#include "memory.h"
#include "panic.h"
#include "printk.h"
#include "riscv.h"
#include "proc.h"

// the kernel pagetable contain all physical memory space
// 256M memory space only need one pagetable to map it
pagetable_t kernel_pagetable;

extern char _etext[];

// find the third pagetable pte of current va
pte_t* walk(pagetable_t pt, uint64_t va, int alloc) {
    if(va >= MAXVA)
        panic("walk error: va bigger than max va");
    
    for(int level = 2; level > 0; level--) {
        pte_t* pte = &pt[PX(level, va)];
        if(*pte & PTE_V) {
            pt = (pagetable_t)PTE2PA(*pte);
        } else {
            if(!alloc || (pt = (pte_t*)kalloc()) == 0)
                return 0;
            memset(pt, 0, PAGE_SIZE);
            *pte = PA2PTE(pt) | PTE_V;
        }
    }
    return &pt[PX(0, va)];
}

int page_map_make(pagetable_t pt, uint64_t va, uint64_t pa, uint64_t size, int perm) {
    uint64_t current_va, pages_count;
    pte_t *pte;
    if((va % PAGE_SIZE) != 0)
        panic("page map error: va not aligned 4K");
    if((size % PAGE_SIZE) != 0)
        panic("page map error: size not aligned 4K");
    if(size == 0)
        panic("page map error: size equal to 0");

    current_va = va;
    pages_count = size / PAGE_SIZE;
    for(int i = 0; i < pages_count; i++) {
        pte = walk(pt, current_va, 1);
        if(pte == 0) return -1;
        if(*pte & PTE_V)
            panic("page map error: remap same page");
        *pte = PA2PTE(pa) | perm | PTE_V;
        current_va += PAGE_SIZE;
        pa += PAGE_SIZE;
    }
    return 0;
}

void page_init() {
    pagetable_t kpagetable;
    kpagetable = (pagetable_t) kalloc();
    memset(kpagetable, 0, PAGE_SIZE);

    int ret = 0;
    
    // UART
    ret += page_map_make(kpagetable, UART0, UART0, PAGE_SIZE, PTE_R | PTE_W);

    // VIRTIO
    ret += page_map_make(kpagetable, VIRTIO0, VIRTIO0, PAGE_SIZE, PTE_R | PTE_W);

    // PLIC
    ret += page_map_make(kpagetable, PLIC, PLIC, PLIC_MMIO_SIZE, PTE_R | PTE_W);

    // SBI
    ret += page_map_make(kpagetable, SBI_START, SBI_START, (KERNEL_START - SBI_START), PTE_R | PTE_X);

    // kernel code
    ret += page_map_make(kpagetable, KERNEL_START, KERNEL_START, ((uint64_t)_etext - KERNEL_START), PTE_R | PTE_X);

    // kernel data and other all
    ret += page_map_make(kpagetable, (uint64_t)_etext, (uint64_t)_etext, (MEMORY_TOP - (uint64_t)_etext), PTE_R | PTE_W);

    ret += proc_stack_map(kpagetable);

    if(ret != 0)
        panic("page init error");

    kernel_pagetable = kpagetable;
    printk("[INIT] finish kernel pages map\n");
}

void page_on() {
    sfence_vma();
    csr_write(satp, MAKE_SATP(kernel_pagetable));
    printk("[INIT] finish kernel page on\n");
    sfence_vma();
}