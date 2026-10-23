
#include <setup.h>
int init_clk(void) {
    REG(XOSC_BASE) &= ~(0xffffff);
    REG(XOSC_BASE) = (XOSC_ENABLE << 12) | XOSC_FREQ_1_15;
    while (!(REG(XOSC_STATUS) & XOSC_STATUS_STABLE));

    REG(CLK_REF_CTRL) = XOSC_CLKSRC;
    while (!(REG(CLK_REF_SELECTED) & CLK_REF_XOSC_SELECTED));

    REG(CLK_SYS_CTRL) &= ~(1);
    while (!(REG(CLK_SYS_SELECTED) & 1));

    REG(CLK_PERI_CTRL) &= ~(CLK_PERI_ENABLE);
    while (REG(CLK_PERI_CTRL) & CLK_PERI_ENABLED);

    REG(CLK_PERI_CTRL) &= ~(7 << 5);
    REG(CLK_PERI_CTRL) |= (4 << 5);
    REG(CLK_PERI_CTRL) |= CLK_PERI_ENABLE;
    REG(CLK_PERI_DIV) |= 1 << 16;
    while (!(REG(CLK_PERI_CTRL) & CLK_PERI_ENABLED));

    return 0;
}
int init_reset(void) {
    volatile int uart_regs[16];
    volatile unsigned int *base = (unsigned int *)RESET_BASE;
    volatile unsigned int *done = (unsigned int *)RESET_DONE;
    volatile unsigned int *uart = (unsigned int *)UART0_BASE;
    init_clk();

    REG(RESET_BASE) |= (RES_IO_BANK0_BIT);
    REG(RESET_BASE) &= ~(RES_IO_BANK0_BIT);
    REG(RESET_BASE) &= ~(RES_PADS_BANK0_BIT);
    REG(RESET_BASE) &= ~(RES_UART0_BIT);

    while (!((((*done) >> 6) & 1) && (((*done) >> 9) & 1) && (((*done) >> 26) & 1)));
    for (int i = 8; i < 12; i++) {
        uart_regs[i] = *(uart + (UART_PERIPHID0)/4);
        uart_regs[i + 4] = *(uart + (UART_PCELLID0)/4);
    }
    (void)uart_regs;
    (void)base;
    return 0;
}

