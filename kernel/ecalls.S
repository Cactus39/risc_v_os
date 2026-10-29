
    .section .text
    .globl sys_sleep
    .globl sys_exit

sys_sleep:
    li      a7,     11
    ecall
    ret

sys_exit:
    li      a7,     60
    ecall
    ret