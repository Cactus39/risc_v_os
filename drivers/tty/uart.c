#include <soc.h>
#include <regs.h>

int init_uart(void) {
    REG(GPIO0_PAD_CTRL) &= ~(GPIO_OD_BIT);
    // REG(GPIO1_PAD_CTRL) &= ~(GPIO_OD_BIT);
    // REG(GPIO0_PAD_CTRL) |= (GPIO_IE_BIT);
    REG(GPIO1_PAD_CTRL) |= (GPIO_IE_BIT);
    REG(GPIO0_PAD_CTRL) &= ~(GPIO_ISO_BIT);
    REG(GPIO1_PAD_CTRL) &= ~(GPIO_ISO_BIT);

    REG(GPIO0_CTRL) &= ~(0x1f);
    REG(GPIO0_CTRL) |= 0x2;  // uart funcsel
    REG(GPIO1_CTRL) &= ~(0x1f);
    REG(GPIO1_CTRL) |= 0x2;  // uart funcsel

    REG(UART0_CR) &= ~1;
    REG(UART0_IBDR) &= ~(0xff);
    REG(UART0_IBDR) |= 6;  // baudrate int
    REG(UART0_FBDR) &= ~(0b111111);
    REG(UART0_FBDR) |= 33;  // baudrate float
    REG(UART0_LCR_H) |= 3 << 5;  // word len 0b11 8 bit
    REG(UART0_LCR_H) |= 1 << 4;  // fifo enable
    REG(UART0_CR) |= (1 << 8 | 1 << 9);
    REG(UART0_CR) |= 1;

    return 0;
}

void    uart_test(char a)
{
    while (REG(UART0_FR) & UART0_FR_TXFF);
    REG(UART0_BASE) = a;
}