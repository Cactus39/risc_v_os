#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>

void    init_tasks(void);
void    start_tasks(void);


int     start_kernel(void) {
    init_clk();
    init_reset();
    init_uart();
    init_tasks();
    start_ticks();
    uprintf("\033c");
    start_tasks();

    // __asm__ __volatile__ ("ecall");
    // __asm__ __volatile__ ("call _fail");
    while (1) {

        // uprintf("\033c");

        uprintf("%d\n", uptime_ms());

        msleep(1000);
    }

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}