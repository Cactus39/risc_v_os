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
    sw      zero,   0(t0)
    addi    t0,     t0,     4
    bne     t0,     t1,     .init_zero

    la       t0,     __data_load
    la       t1,     __data_start
    la       t2,     __data_end
.init_data:
    beq     t1,     t2,     .data_fin
    lw      a0,     0(t0)
    sw      a0,     0(t1)
    addi    t1,     t1,     4
    addi    t0,     t0,     4
    j       .init_data
.data_fin:

    addi    s0,     zero,   0
.loop:
    nop
    addi    s0,     s0,     1
    nop
    ecall

    j       .loop

.sleep:
    wfi
    j       .sleep

    .balign 4

.trap:
    csrr    a0, mcause
    csrr    a1, mepc
    csrr    a2, mtval
    csrr    a3, mstatus
    j       .trap
