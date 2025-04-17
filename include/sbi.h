#ifndef __TAOS_SBI_H__
#define __TAOS_SBI_H__

#include "sbi_ecall_interface.h"
#include "stdint.h"

struct sbiret {
    uint64_t error;
    uint64_t value;
};

struct sbiret sbi_ecall(uint64_t eid, uint64_t fid,
                        uint64_t arg0, uint64_t arg1, uint64_t arg2,
                        uint64_t arg3, uint64_t arg4, uint64_t arg5);

// struct sbiret sbi_set_timer(uint64_t stime_value);
struct sbiret sbi_debug_console_write_byte(uint8_t byte);
struct sbiret sbi_system_reset(uint32_t reset_type, uint32_t reset_reason);

#endif