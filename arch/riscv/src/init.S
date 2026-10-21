    .section .text
    .globl _start

_start:
    csrr    t0,     mhartid
    bnez    t0,     .sleep
    la      sp,     __stack_top
    la      t0,     trap_entry
    csrw    mtvec,  t0

    la      t0,     __bss_start
    la      t1,     __bss_end
.init_zero:
    bgeu    t0,     t1,     .zero_fin
    sw      zero,   0(t0)
    addi    t0,     t0,     4
    j       .init_zero
.zero_fin:

    la       t0,     __data_load
    la       t1,     __data_start
    la       t2,     __data_end
.init_data:
    bgeu    t1,     t2,     .data_fin
    lw      t5,     0(t0)
    sw      t5,     0(t1)
    addi    t1,     t1,     4
    addi    t0,     t0,     4
    j       .init_data
.data_fin:

    call    main

.sleep:
    wfi
    j       .sleep
