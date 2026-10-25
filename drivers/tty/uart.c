#include <soc.h>
#include <regs.h>
#include <stdarg.h>

int init_uart(void) {
    gpio_pad_set(0, 0, 0);  // pin od ie
    gpio_pad_set(1, 0, 1);

    gpio_io_set(0, 2);  // pin funcsel 2 == uart
    gpio_io_set(1, 2);

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

int uart_putchar(const unsigned char a){
    if (a == '\n')
        uart_putchar('\r');
    while (REG(UART0_FR) & UART0_FR_TXFF);
    REG(UART0_BASE) = a;
    return (a != '\r' ? 1 : 0);
}

int uart_puts(const char *s) {
    register int c = 0;
    if (s == (void *)0)
        return (0);
    while (*s) {
        c += uart_putchar(*s);
        s++;
    }
    return (c);
}

int uart_putnbr(int a) {
    register int c = 0;
    if (a < 0) {
        if (a == (int)0x80000000) {
            c += uart_puts("-2147483648");
            return (c);
        }
        c += uart_putchar('-');
        a *= -1;
    }
    if (a < 10 && a >= 0) {
        c += uart_putchar(a + '0');
    }
    else {
        c += uart_putnbr(a / 10);
        c += uart_putchar(a % 10 + '0');
    }
    return (c);
}

int uart_putaddr(unsigned int a) {
    unsigned int nibble;
    uart_puts("0x");
    for (int i = 28; i >= 0; i -= 4) {
        nibble = (a >> i & 0xf);
        uart_putchar(nibble < 10 ? nibble + '0' : nibble - 10 + 'a');
    }
    return (10);
}

int uart_putnbr_h(unsigned int a) {
    unsigned int nibble;
    for (int i = 28; i >= 0; i -= 4) {
        nibble = (a >> i & 0xf);
        uart_putchar(nibble < 10 ? nibble + '0' : nibble - 10 + 'a');
    }
    return (8);
}
int uart_putnbr_u(const unsigned int a) {
    register int c = 0;
    if (a < 10) {
        c += uart_putchar(a + '0');
    }
    else {
        c += uart_putnbr_u(a / 10);
        c += uart_putchar(a % 10 + '0');
    }
    return (c);
}


int uprintf(const char *s, ...) {
    register    int c = 0;
    va_list     args;
    if (s == (void *)0)
        return (-1);
    va_start(args, s);
    while (*s) {
        if (*s == '%' && *(s + 1)) {
            s++;
            if (*s == 'd') {
                c += uart_putnbr(va_arg(args, int));
            }
            else if (*s == 'p' || *s == 'x')
                c += uart_putaddr(va_arg(args, unsigned int));
            else if (*s == 'c')
                c += uart_putchar(va_arg(args, int));
            else if (*s == 'u')
                c += uart_putnbr_u(va_arg(args, unsigned int));
            else if (*s == 's')
                c += uart_puts(va_arg(args, char *));
            else if (*s == '%')
                c += uart_putchar('%');
            else
                continue ;
            s++;
        }
        else {
            c += uart_putchar(*s);
            s++;
        }
    }
    va_end(args);
    return (c);
}















