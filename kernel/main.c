#include "memory.h"
#include "printk.h"
#include "panic.h"
#include "sbi.h"

// __attribute__ ((aligned(16))) char stack[4096];

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
    page_init();
    return 0;    
}