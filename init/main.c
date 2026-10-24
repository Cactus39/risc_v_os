#include <soc.h>

int     counter = 5;

int     main(void) {
    init_clk();
    init_reset();
    init_uart();
    int res;
    while (1) {
        uart_puts("\033c");

        res = uprintf("%d %x l%ine%%\n",12,11);
        uprintf("%d\n", res);
    }

    for (;;) {
        counter++;
        __asm__ __volatile__ ("" ::: "memory");
    }
}