    .equ FRAME_SIZE, 144

.section .text
    .globl trap_entry
    .balign 4

trap_entry:
    addi    sp,     sp,     -FRAME_SIZE
    .irp r, 1,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sw      x\r,    4*\r(sp)
    .endr

    addi    t0,     sp,     FRAME_SIZE
    sw      t0,     8(sp)

    csrr    t0,     mepc
    sw      t0,     32*4(sp)
    csrr    t0,     mcause
    sw      t0,     33*4(sp)
    csrr    t0,     mtval
    sw      t0,     34*4(sp)

    mv      a0,     sp
    call    do_trap

    lw      t0,     32*4(sp)
    csrw    mepc,   t0

    .irp r, 1,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    lw      x\r,    4*\r(sp)
    .endr

    addi    sp,     sp,     FRAME_SIZE
    mret
