
.global dead_loop
.global init_thread1

init_thread1:
    la t0, dead_loop
    csrw sepc, t0
    sret