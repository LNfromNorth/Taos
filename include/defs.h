#ifndef __TAOS_DEFS_H__
#define __TAOS_DEFS_H__

#include "stdint.h"

// memory
void memory_init();
void* kalloc();
void kfree(uint64_t addr);

#endif
