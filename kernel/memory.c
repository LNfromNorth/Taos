#include "memory.h"
#include "mbr.h"
#include "panic.h"
#include "printk.h"
#include "stdint.h"
#include <string.h>

extern char _ekernel[];

// static int32_t mmap[PAGE_NUMS(PHYMEM_SIZE)] = {0};

// -------------------------------
// physical memory alloc and free
// -------------------------------

#define VA2PA(x) ((x - (uint64_t)PA2VA_OFFSET))
#define PA2VA(x) ((x + (uint64_t)PA2VA_OFFSET))
#define PFN2PHYS(x) (((uint64_t)(x) << 12) + PHYMEM_START)
#define PHYS2PFN(x) (((uint64_t)(x) - PHYMEM_START) >> 12)

#define LEFT_LEAF(index) ((index) * 2 + 1)
#define RIGHT_LEAF(index) ((index) * 2 + 2)
#define PARENT(index) (((index) + 1) / 2 - 1)
#define IS_POWER_OF_2(x) (!((x) & ((x) - 1)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void *free_page_start = &_ekernel;
struct buddy buddy;

uint64_t buddy_alloc(uint64_t nrpages);

static uint64_t fixsize(uint64_t size) {
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size |= size >> 32;
    return size + 1;
}

void buddy_init() {
    uint64_t buddy_size = (uint64_t)PHYMEM_SIZE / PAGE_SIZE;
    if (!(IS_POWER_OF_2(buddy_size))) {
        buddy_size = fixsize(buddy_size);
    }
    buddy.size = buddy_size;
    buddy.bitmap = free_page_start;
    free_page_start += 2 * buddy.size * sizeof(*buddy.bitmap);
    memset(buddy.bitmap, 0, 2 * buddy.size * sizeof(*buddy.bitmap));

    uint64_t node_size = buddy.size * 2;
    for (uint64_t i = 0; i < 2 * buddy_size - 1; ++i) {
        if (IS_POWER_OF_2(i + 1))
            node_size /= 2;
        buddy.bitmap[i] = node_size;
    }

    for (uint64_t pfn = 0;
         (uint64_t)PFN2PHYS(pfn) < VA2PA((uint64_t)free_page_start); ++pfn) {
        buddy_alloc(1);
    }

    printk("[INIT] finish buddy init\n");
    return;
}

void buddy_free(uint64_t pfn) {
    uint64_t node_size, index = 0;
    uint64_t left_longest, right_longest;

    node_size = 1;
    index = pfn + buddy.size - 1;

    for (; buddy.bitmap[index]; index = PARENT(index)) {
        node_size *= 2;
        if (index == 0)
            break;
    }

    buddy.bitmap[index] = node_size;

    while (index) {
        index = PARENT(index);
        node_size *= 2;

        left_longest = buddy.bitmap[LEFT_LEAF(index)];
        right_longest = buddy.bitmap[RIGHT_LEAF(index)];

        if (left_longest + right_longest == node_size)
            buddy.bitmap[index] = node_size;
        else
            buddy.bitmap[index] = MAX(left_longest, right_longest);
    }
}

uint64_t buddy_alloc(uint64_t nrpages) {
    uint64_t index = 0;
    uint64_t node_size;
    uint64_t pfn = 0;

    if (nrpages <= 0)
        nrpages = 1;
    else if (!IS_POWER_OF_2(nrpages))
        nrpages = fixsize(nrpages);

    if (buddy.bitmap[index] < nrpages)
        return 0;

    for (node_size = buddy.size; node_size != nrpages; node_size /= 2) {
        if (buddy.bitmap[LEFT_LEAF(index)] >= nrpages)
            index = LEFT_LEAF(index);
        else
            index = RIGHT_LEAF(index);
    }

    buddy.bitmap[index] = 0;
    pfn = (index + 1) * node_size - buddy.size;

    while (index) {
        index = PARENT(index);
        buddy.bitmap[index] = MAX(buddy.bitmap[LEFT_LEAF(index)],
                                  buddy.bitmap[RIGHT_LEAF(index)]);
    }

    return pfn;
}

void *alloc_pages(uint64_t nrpages) {
    uint64_t pfn = buddy_alloc(nrpages);
    if (pfn == 0)
        return 0;
    return (void *)(PA2VA(PFN2PHYS(pfn)));
}

void *alloc_page() { return alloc_pages(1); }

void free_pages(void *va) { buddy_free(PHYS2PFN(VA2PA((uint64_t)va))); }

// default get new pages from end of mmap
void *kalloc() {
    // int index;
    // for (int i = PAGE_NUMS(PHYMEM_SIZE) - 1; i > 0; i--) {
    //     if (mmap[i] == 0) {
    // index = i;
    // break;
    // }
    // }
    // mmap[index] = 1; // set mmap used
    // return (void *)(uint64_t)(PHYMEM_START + (index << 12));
    return alloc_page();
}

void kfree(void *addr) {
    // int index = ((addr - PHYMEM_START) & 0xfffff000) >> 12;
    // if (mmap[index] == 0) {
    //     panic("free illgle page");
    // }
    // mmap[index] = 0;
    free_pages(addr);
    return;
}

void kfreerange(char *start, char *end) {
    char *addr = (char *)PGROUNDUP((uint64_t)start);
    for (; (uintptr_t)(addr) + PAGE_SIZE <= (uintptr_t)end; addr += PAGE_SIZE) {
        kfree((void *)addr);
    }
}

// init mmap, set kernel and sbi space to 1, others to 0
void mmap_init() {
    // int used_pages = PAGE_NUMS(((uint64_t)_ekernel - PHYMEM_START));
    // int total_pages = PAGE_NUMS(PHYMEM_SIZE);
    // int i = 0;
    // for (; i < used_pages; i++) {
    //     mmap[i] = 1; // set used pages to 1
    // }
    // for (; i < total_pages; i++) {
    //     mmap[i] = 0;
    // }
    return;
}

void memory_init() {
    // set bitmap for memory
    // mmap_init();
    buddy_init();
    printk("[INIT] finish mmap init\n");
}
