#include <soc.h>

int     counter = 5;

int     main(void) {
    init_uart();
    while (1)
        uart_test('q');

    for (;;) {
        counter++;
        __asm__ __volatile__ ("" ::: "memory");
    }
}