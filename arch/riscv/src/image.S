.section .MBR, "a"
.balign 4
MBR_start:
    .word 0xffffded3
    .byte 0x42, 0x01
    .hword 0x1101
    .byte 0x44, 0x03
    .hword 0
    .word _start
    .word __stack_top
    .byte 0xff
    .hword (MBR_end - MBR_start - 16) / 4
    .byte 0
    .word 0
    .word 0xab123579
MBR_end:
