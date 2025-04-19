#ifndef __TAOS_MEMORY_H__
#define __TAOS_MEMORY_H__

#include "stdint.h"

// use SV39
// 64bit one entry
// | phyaddr | 10bit |
typedef uint64_t* pagetable_t;
typedef uint64_t pte_t;

// physical memory size
#define PHYMEM_SIZE     (1L << 28)
// physical memory start addr
#define PHYMEM_START    0x80000000
// sbi firmware memory start addr
#define SBI_START       0x80000000
// kernel memory start addr
#define KERNEL_START    0x80400000
// memory top
#define MEMORY_TOP      0x90000000

// FOR PAGES
// size of page
#define PAGE_SIZE       (1L << 12)
// calculate the nums of pages
#define PAGE_NUMS(size) ((size) / PAGE_SIZE)
// total pages num
#define TOTAL_PAGES     (1L << 16)
// permision of pte
#define PTE_V           (1L << 0)   // valid
#define PTE_R           (1L << 1)   // read
#define PTE_W           (1L << 2)   // write
#define PTE_X           (1L << 3)   // execute
#define PTE_U           (1L << 4)   // user
// shift of physical address in pte
#define PA2PTE(pa)      ((((uint64_t)pa) >> 12) << 10)
#define PTE2PA(pte)     (((pte) >> 10) << 12)
#define PTE_FLAGS(pte)  ((pte) & 0x3FF)
// get entry offset of current table level
#define PGSHIFT         12
#define PXMASK          0x1FF // 9 bits
#define PXSHIFT(level)  (PGSHIFT + (9 * (level)))
#define PX(level, va)   ((((uint64_t) (va)) >> PXSHIFT(level)) & PXMASK)

#define MAXVA           (1L << (9 + 9 + 9 + 12 - 1))


// memory
void memory_init();
void* kalloc();
void kfree(uint64_t addr);

// page
void page_init();

#endif
