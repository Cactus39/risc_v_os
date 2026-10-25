#include <regs.h>

int init_clk(void) {
    register int n = 1000000;
    REG(XOSC_BASE) &= ~(0xffffff);
    REG(XOSC_BASE) |= (XOSC_ENABLE << 12) | XOSC_FREQ_1_15;
    while (!(REG(XOSC_STATUS) & XOSC_STATUS_STABLE) && --n);
    if (!n)
        return (-1);

    n = 1000;
    REG(CLK_REF_CTRL) = XOSC_CLKSRC;
    while (!(REG(CLK_REF_SELECTED) & CLK_REF_XOSC_SELECTED) && --n);
    if (!n)
        return (-1);

    n = 1000;
    REG(CLK_SYS_CTRL) &= ~(1);
    while (!(REG(CLK_SYS_SELECTED) & 1) && --n);
    if (!n)
        return (-1);

    n = 1000;
    REG(CLK_PERI_CTRL) &= ~(CLK_PERI_ENABLE);
    while ((REG(CLK_PERI_CTRL) & CLK_PERI_ENABLED) && --n);
    if (!n)
        return (-1);

    n = 1000;
    REG(CLK_PERI_CTRL) &= ~(7 << 5);  // clear all
    REG(CLK_PERI_CTRL) |= (4 << 5);  // turn xosc src
    REG(CLK_PERI_CTRL) |= CLK_PERI_ENABLE;
    REG(CLK_PERI_DIV) |= 1 << 16;  // int part of clk divisor
    while (!(REG(CLK_PERI_CTRL) & CLK_PERI_ENABLED) && --n);
    if (!n)
        return (-1);
    return 0;
}

void    start_ticks(void) {

    REG(TICKS_RISCV_CYCLES) &= ~0x1ff;
    REG(TICKS_RISCV_CYCLES) |= 0xc;
    REG(TICKS_RISCV_CTRL) |= 1;
}

void set_mtimecmp(unsigned int tics) {
    unsigned int mtime;
    unsigned int mtimeh;
    unsigned int mtimeh_2;
    mtimeh = REG(MTIMEH);
    mtime = REG(MTIME);
    mtimeh_2 = REG(MTIMEH);
    while (mtimeh != mtimeh_2) {
        mtimeh = REG(MTIMEH);
        mtime = REG(MTIME);
        mtimeh_2 = REG(MTIMEH);
    }
    REG(MTIMECMP) = 0xffffffff;
    REG(MTIMECMPH) = mtimeh;
    REG(MTIMECMP) = mtime + tics;
}


