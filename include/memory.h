#ifndef __TAOS_MEMORY_H__
#define __TAOS_MEMORY_H__

// physical memory size
#define PHYMEM_SIZE     (1 << 28)
// physical memory start addr
#define PHYMEM_START    0x80000000
// sbi firmware memory start addr
#define SBI_START       0x80000000
// kernel memory start addr
#define KERNEL_START    0x80400000

// size of page
#define PAGE_SIZE      (1 << 12)
// calculate the nums of pages
#define PAGE_NUMS(size) ((size) / PAGE_SIZE)
// total pages num
#define TOTAL_PAGES     (1 << 16)

#endif
