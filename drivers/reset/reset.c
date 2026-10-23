#include <regs.h>
#include <soc.h>

int init_reset(void) {
    register int n;
    unsigned int mask = (RES_IO_BANK0_BIT | RES_PADS_BANK0_BIT | RES_UART0_BIT);

    n = init_clk();
    if (!n)
        return (-1);
    REG(RESET_BASE) &= ~(mask);
    n = 1000;
    while (--n && !((REG(RESET_DONE) & mask) == mask));
    if (!n)
        return (-1);

    return 0;
}