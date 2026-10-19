.section .embedded_block, "a"
.balign 4
embedded_block_start:
    .word 0xffffded3
    .byte 0x42, 0x01
    .hword 0x1101
    .byte 0x44, 0x03
    .hword 0
    .word _start
    .word __stack_top
    .byte 0xff
    .hword (embedded_block_end - embedded_block_start - 16) / 4
    .byte 0
    .word 0
    .word 0xab123579
embedded_block_end:

    .section .text
    .globl _start
_start:
    csrr    t0, mhartid
    bnez    t0, .sleep
    la      sp, __stack_top
    la      t0, .trap
    csrw    mtvec, t0



.loop:

    j       .loop



.sleep:
    wfi
    j       .sleep

    .balign 4

.trap:
    csrr    a0, mcause
    csrr    a1, mepc
    csrr    a2, mtval
    j       .trap
