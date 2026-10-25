#include <regs.h>

void    gpio_io_set(int pin, int funcsel) {
    volatile unsigned int *status;
    volatile unsigned int *ctrl;

    status = (unsigned int *)(IO_BANK0_BASE + (pin * 8));
    ctrl = status + 1;
    *ctrl &= ~(0x1f);
    *ctrl |= funcsel;  // uart 2
}

void gpio_pad_set(int pin, int od, int ie) {
    volatile unsigned int *base_register = (unsigned int *)PADS_BANK0_BASE;
    unsigned int mask = *(base_register + pin + 1);
    mask &= ~((!od << 7) | (!ie << 6));
    mask |= ((od << 7) | (ie << 6));
    *(base_register + pin + 1) = mask;
    *(base_register + pin + 1) &= ~(GPIO_ISO_BIT);
}
