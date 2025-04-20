#ifndef __TAOS_PROC_H__
#define __TAOS_PROC_H__

#include "stdint.h"
#include "memory.h"

// nums of total procs
#define NPROC   64

// saved registers for kernel context switch
struct context {
  uint64_t ra;
  uint64_t sp;

  // callee-saved
  uint64_t s0;
  uint64_t s1;
  uint64_t s2;
  uint64_t s3;
  uint64_t s4;
  uint64_t s5;
  uint64_t s6;
  uint64_t s7;
  uint64_t s8;
  uint64_t s9;
  uint64_t s10;
  uint64_t s11; 
};

// saved trap frame 
struct trapframe {
  /*   0 */ uint64_t kernel_satp;   // kernel page table
  /*   8 */ uint64_t kernel_sp;     // top of process's kernel stack
  /*  16 */ uint64_t kernel_trap;   // usertrap()
  /*  24 */ uint64_t epc;           // saved user program counter
  /*  32 */ uint64_t kernel_hartid; // saved kernel tp
  /*  40 */ uint64_t ra;
  /*  48 */ uint64_t sp;
  /*  56 */ uint64_t gp;
  /*  64 */ uint64_t tp;
  /*  72 */ uint64_t t0;
  /*  80 */ uint64_t t1;
  /*  88 */ uint64_t t2;
  /*  96 */ uint64_t s0;
  /* 104 */ uint64_t s1;
  /* 112 */ uint64_t a0;
  /* 120 */ uint64_t a1;
  /* 128 */ uint64_t a2;
  /* 136 */ uint64_t a3;
  /* 144 */ uint64_t a4;
  /* 152 */ uint64_t a5;
  /* 160 */ uint64_t a6;
  /* 168 */ uint64_t a7;
  /* 176 */ uint64_t s2;
  /* 184 */ uint64_t s3;
  /* 192 */ uint64_t s4;
  /* 200 */ uint64_t s5;
  /* 208 */ uint64_t s6;
  /* 216 */ uint64_t s7;
  /* 224 */ uint64_t s8;
  /* 232 */ uint64_t s9;
  /* 240 */ uint64_t s10;
  /* 248 */ uint64_t s11;
  /* 256 */ uint64_t t3;
  /* 264 */ uint64_t t4;
  /* 272 */ uint64_t t5;
  /* 280 */ uint64_t t6;
};

// think about the state of proc
enum proc_state { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// refer to xv6 proc design
struct proc {
    int pid;

    enum proc_state state;
    void* chan;
    int killed;
    int xstate; 

    struct proc *parent;

    uint64_t kstack;
    uint64_t mem_size;
    pagetable_t pagetable;    
    struct trapframe *trapframe;
    struct context context;
    // TODO: use after support file system
    // struct file *ofile[NOFILE];
    // struct inode *cwd;
    char name[16];
};

void proc_init();
int proc_stack_map(pagetable_t kpagetable);

#endif
