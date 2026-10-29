.section .text
    .globl irq_enable
    .globl irq_disable
    .globl irq_save
    .globl irq_restore

irq_enable:
        csrsi       mstatus,    8
        ret

irq_disable:
        csrci       mstatus,    8
        ret

irq_save:
        csrrci  a0, mstatus,    8
        ret

irq_restore:
        andi    a0,     a0,     8
        bnez    a0,     irq_enable
        ret
