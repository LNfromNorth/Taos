#include "printk.h"

#define TAOS_VERSION "Taos v0.1\n"
#define TAOS_TITLE_0 "  _________   ____  _____\n"
#define TAOS_TITLE_1 " /_  __/   | / __ \\/ ___/\n"
#define TAOS_TITLE_2 "  / / / /| |/ / / /\\__ \\ \n"
#define TAOS_TITLE_3 " / / / ___ / /_/ /___/ / \n"
#define TAOS_TITLE_4 "/_/ /_/  |_\\____//____/  \n"
                         

int main() {
    printk(TAOS_VERSION);
    printk(TAOS_TITLE_0);
    printk(TAOS_TITLE_1);
    printk(TAOS_TITLE_2);
    printk(TAOS_TITLE_3);
    printk(TAOS_TITLE_4);
    // memory init
    // trap init
    // fs init
}