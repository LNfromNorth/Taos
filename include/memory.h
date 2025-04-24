#ifndef __TAOS_MEMORY_H__
#define __TAOS_MEMORY_H__

#include "stdint.h"

// use SV39
// 64bit one entry
// | phyaddr | 10bit |
typedef uint64_t* pagetable_t;
typedef uint64_t pte_t;

// Device mmio map
// Define in qemu-6.2 -> hw/riscv/vrit.c
// static const MemMapEntry virt_memmap[] = {
//     [VIRT_DEBUG] =       {        0x0,         0x100 },
//     [VIRT_MROM] =        {     0x1000,        0xf000 },
//     [VIRT_TEST] =        {   0x100000,        0x1000 },
//     [VIRT_RTC] =         {   0x101000,        0x1000 },
//     [VIRT_CLINT] =       {  0x2000000,       0x10000 },
//     [VIRT_ACLINT_SSWI] = {  0x2F00000,        0x4000 },
//     [VIRT_PCIE_PIO] =    {  0x3000000,       0x10000 },
//     [VIRT_PLIC] =        {  0xc000000, VIRT_PLIC_SIZE(VIRT_CPUS_MAX * 2) },
//     [VIRT_UART0] =       { 0x10000000,         0x100 },
//     [VIRT_VIRTIO] =      { 0x10001000,        0x1000 },
//     [VIRT_FW_CFG] =      { 0x10100000,          0x18 },
//     [VIRT_FLASH] =       { 0x20000000,     0x4000000 },
//     [VIRT_PCIE_ECAM] =   { 0x30000000,    0x10000000 },
//     [VIRT_PCIE_MMIO] =   { 0x40000000,    0x40000000 },
//     [VIRT_DRAM] =        { 0x80000000,           0x0 },
// };

// Copy from xv6 memlayout.h
// qemu puts UART registers here in physical memory.
// we will not use UART mmio, use SBI interface to read/write to console
#define UART0 0x10000000L
#define UART0_IRQ 10

// virtio mmio interface
#define VIRTIO0 0x10001000
#define VIRTIO0_IRQ 1

// qemu puts platform-level interrupt controller (PLIC) here.
#define PLIC 0x0c000000L
#define PLIC_PRIORITY (PLIC + 0x0)
#define PLIC_PENDING (PLIC + 0x1000)
#define PLIC_SENABLE(hart) (PLIC + 0x2080 + (hart)*0x100)
#define PLIC_SPRIORITY(hart) (PLIC + 0x201000 + (hart)*0x2000)
#define PLIC_SCLAIM(hart) (PLIC + 0x201004 + (hart)*0x2000)

#define PLIC_MMIO_SIZE  0x4000000


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

// max va
#define MAXVA           (1L << (9 + 9 + 9 + 12 - 1))

// trampoline page map va
#define TRAMPOLINE (MAXVA - PAGE_SIZE)

// map of proc stack space
#define KSTACK(p) (TRAMPOLINE - ((p) + 1)* 2 * PAGE_SIZE)


// memory
void memory_init();
void* kalloc();
void kfree(uint64_t addr);

// page
void page_init();
void page_on();
int page_map_make(pagetable_t pt, uint64_t va, uint64_t pa, uint64_t size, int perm);


#endif
