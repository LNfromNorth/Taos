# XV6-riscv

> this doc will introduce some parts of xv6 operating system.

## before main (some prework)

- set stack for c running
- set mode to S-mode
- set clock interrupt
- disable paging ?

## main (init all things)

- console
- printf
- kinit(PMem)
- kvm(kernel page table)
- proc
- trap
- plic(interrupt control)
- buffer cache
- inode
- filesystem
- virtio-disk
- user

## after main

- scheduler