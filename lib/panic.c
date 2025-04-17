#include "printk.h"
#include "sbi.h"

void panic(char* message) {
    printk("[PANIC] system panic because: \n-> %s\n", message);
    sbi_system_reset(0, 1);
}