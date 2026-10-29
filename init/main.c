#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>
#include <schedule.h>


int     start_kernel(void) {
    init_clk();
    init_reset();
    init_uart();
    uprintf("\033c");
    add_task();
    start_ticks();
    start_tasks();

    // __asm__ __volatile__ ("ecall");
    // __asm__ __volatile__ ("call _fail");
    while (1)
    {
        // uprintf("\033c");
        uprintf("%d\n", uptime_ms());

        msleep(1000);
    }

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}