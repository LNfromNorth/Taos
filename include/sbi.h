#ifndef __TAOS_SBI_H__
#define __TAOS_SBI_H__

#define SBI_ECALL(__num, __a0, __a1, __a2)                          \
({                                                                  \
    register unsigned long a0 asm("a0") = (unsigned long)(__a0);   \
    register unsigned long a1 asm("a1") = (unsigned long)(__a1);   \
    register unsigned long a2 asm("a2") = (unsigned long)(__a2);   \
    register unsigned long a7 asm("a7") = (unsigned long)(__num);  \
    asm volatile("ecall"                                            \
                    : "+r"(a0)                                      \
                    : "r"(a1), "r"(a2), "r"(a7)                     \
                    : "memory");                                    \
    a0;                                                             \
})

#define SBI_ECALL_0(__num)                      SBI_ECALL(__num, 0, 0, 0)
#define SBI_ECALL_1(__num, __a0)                SBI_ECALL(__num, __a0, 0, 0)
#define SBI_ECALL_2(__num, __a0, __a1)          SBI_ECALL(__num, __a0, __a1, 0)
#define SBI_ECALL_3(__num, __a0, __a1, __a2)    SBI_ECALL(__num, __a0, __a1, __a2)

#endif