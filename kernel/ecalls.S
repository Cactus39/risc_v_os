    .section .text
    .globl __sys_sleep

__sys_sleep:
    li      a7,     11
    ecall
    ret
