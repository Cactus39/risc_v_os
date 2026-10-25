#include <soc.h>
#include <regs.h>
#include <setup.h>
int     counter = 5;

int     start_kernel(void) {
    init_clk();
    init_reset();
    init_uart();
    start_ticks();
    int res;
    set_mtimecmp(1000000);
    __asm__ __volatile__ ("csrs mie, %0":: "r"(128));
    __asm__ __volatile__ ("csrs mstatus, %0":: "r"(8));

    while (1)
        __asm__ __volatile__ ("wfi");
    while (0) {

        uart_puts("\033c");
        char *line = "%d %x l%ine%%\n";
        res = uprintf(line,12,11);
        uprintf("%d\n", res);
    }

    for (;;) {
        counter++;
        REG(0xd00001b0) = 0xffffffff;
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}