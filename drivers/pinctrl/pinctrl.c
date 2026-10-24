#include <regs.h>

int gpio_io_set(int pin, int funcsel) {
    // 40070000 Bank 0
    // 40078000 Bank 1
    volatile unsigned int *status;
    volatile unsigned int *ctrl;
    register int n = 1000;

    status = (unsigned int *)(IO_BANK0_BASE + (pin * 8));
    ctrl = status + 1;
    *ctrl &= ~(0x1f);
    *ctrl |= funcsel;  // uart 2
    while (--n && !(((*status) >> 13) & 1));
    if (!n)
        return (-1);
    return 0;
}

void gpio_pad_set(int pin, int od, int ie) {
    volatile unsigned int *base_register = (unsigned int *)PADS_BANK0_BASE;
    *(base_register + pin + 1) &= ~((!od << 7) | (!ie << 6));
    *(base_register + pin + 1) |= ((od << 7) | (ie << 6));
    *(base_register + pin + 1) &= ~(GPIO_ISO_BIT);
}
