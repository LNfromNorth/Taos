#ifndef __TAOS_RISCV_H__
#define __TAOS_RISCV_H__

#include "stdint.h"

// sstatus
#define SSTATUS_SIE   (1L << 1)
#define SSTATUS_SPIE  (1L << 5)
#define SSTATUS_SPP   (1L << 8)

// sie
#define SIE_STIE    (1L << 5)



#define csr_read(csr)                   \
  ({                                    \
    uint64_t __v;                       \
    asm volatile("csrr %0, " #csr :"=r" (__v) : : "memory"); \
    __v;                                \
  })

#define csr_write(csr, val)                                    \
  ({                                                           \
    uint64_t __v = (uint64_t)(val);                            \
    asm volatile("csrw " #csr ", %0" : : "r"(__v) : "memory"); \
  })

#define SATP_SV39     (8L << 60)
#define MAKE_SATP(pagetable) (SATP_SV39 | (((uint64_t)pagetable) >> 12))

// flush the TLB
static inline void sfence_vma() {
  asm volatile("sfence.vma zero, zero");
}

#endif