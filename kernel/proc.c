#include "proc.h"
#include "panic.h"
#include "printk.h"
#include "lib/string.h"

struct proc procs[NPROC];
void swtch(struct context*, struct context*);
void init_thread1();

static struct proc* current;

int proc_stack_map(pagetable_t kpagetable) {
    int ret = 0;
    for (int i = 0; i < NPROC; i++) {
        uint64_t pa = (uint64_t)kalloc();
        if (pa == 0)
            panic("proc stack map error: no free pages");
        uint64_t va = KSTACK((int)(i));
        ret += page_map_make(kpagetable, va, pa, PAGE_SIZE, PTE_W | PTE_R);
    }
    return ret;
}

void proc_init() {
    for (int i = 0; i < NPROC; i++) {
        procs[i].state = UNUSED;
        procs[i].kstack = KSTACK((int)(i));
    }
    printk("[INIT] finish proc init\n");
}

void schedule() {

    struct proc* p;
    int runnable = 0;
    
    for(int i = 0; i < NPROC; i++) {
        if(procs[i].state == RUNNABLE) {
            p = &procs[i]; 
            runnable = 1;
            break;
        }
    }
    if(runnable) {
        p->state = RUNNING;
        struct proc* c = current;
        c->state = RUNNABLE;
        current = p;
        // printk("[DEBUG] switch to %d\n", p->pid);
        swtch(&c->context, &p->context);
        // printk("[DEBUG] switch back to %d\n", c->pid);
    }
    return;

}

// void yield() {
//     current->state = RUNNABLE;
// 
// }

void dead_loop() {
    while(1);
    // printk("This thread 0 called\n");
    // while(1) {
    //     for(int i = 0; i < 1000; i++) {
    //     }
    //     printk("A");
    // }
}

void kernel_thread1() {
    printk("This is test thread 1 begin\n");

    for(int i = 0; i < 5; i++) {
        printk("Thread 1 output\n");
    }
    // while(1) {
    //     for(int i = 0; i < 1000; i++) {
    //     }
    //     printk("B");
    // }
    printk("This is test thread 1 end\n");
}

void proc_test() {
    char* name = "thread 0";
    procs[0].pid = 0;
    procs[0].state = RUNNING;
    strncpy(procs[0].name, name, strlen(name));
    procs[0].context.ra = (uint64_t)init_thread1;
    procs[0].context.sp = (uint64_t)kalloc();

    name = "thread 1";
    procs[1].pid = 1;
    procs[1].state = RUNNABLE;
    strncpy(procs[1].name, name, strlen(name));
    procs[1].context.ra = (uint64_t)init_thread1;
    procs[1].context.sp = (uint64_t)kalloc();

    current = &procs[0];
    // struct context cur_context;
    // current = &procs[0];
    // current->state = RUNNING;
    // swtch(&cur_context, &current->context);
    // schedule();
}