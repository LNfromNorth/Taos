#include "printk.h"
#include "panic.h"
#include "defs.h"
#include "sbi.h"

__attribute__ ((aligned(16))) char stack[4096];

#define TAOS_VERSION "Taos v0.1\n"
#define TAOS_TITLE_0 "  _________   ____  _____\n"
#define TAOS_TITLE_1 " /_  __/   | / __ \\/ ___/\n"
#define TAOS_TITLE_2 "  / / / /| |/ / / /\\__ \\ \n"
#define TAOS_TITLE_3 " / / / ___ / /_/ /___/ / \n"
#define TAOS_TITLE_4 "/_/ /_/  |_\\____//____/  \n"
                         
// void sbi_message(); 
int init();

int main() {
    printk(TAOS_VERSION);
    printk(TAOS_TITLE_0);
    printk(TAOS_TITLE_1);
    printk(TAOS_TITLE_2);
    printk(TAOS_TITLE_3);
    printk(TAOS_TITLE_4);
    // opensbi message
    // sbi_message();

    init();
    uint64_t pages[10];
    for(int i = 0; i < 10; i++) {
        pages[i] = (uint64_t)kalloc();
        printk("alloc %d page addr is %x\n", i, pages[i]);
    }
    for(int i = 9; i >= 0; i--) {
        kfree(pages[i]);
    }
    printk("[DEBUG] pass kalloc and kfree func");
    uint64_t page = (uint64_t)kalloc(); 
    printk("alloc page addr is %x\n", page);
    kfree(page);

    printk("[DEBUG] test kalloc and kfree successfully!\n");

    panic("Kernel Init Panic!");
    // shutdown
    sbi_system_reset(0, 0);

    while(1);
    // memory init
    // trap init
    // fs init
}

int init() {
    memory_init();
    return 0;    
}

// printk fix
// void sbi_message() {
//     struct sbiret sret = sbi_ecall(0x10, 0, 0, 0, 0, 0, 0, 0);
//     // printk("SBI spec Version: %d.%d\n", sret.value >> 24, sret.value & 0xFFFFFF);
//     printk("SBI spec Version: %d\n", sret.value);
// }