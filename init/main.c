#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>
#include <schedule.h>


int     start_kernel(void) {
    init_clk();
    init_reset();
    init_uart();
    // uprintf("\033c");
    // udelay(10000);
    // uprintf("[started]");
    add_task();
    start_ticks();
    start_tasks();
    // __asm__ __volatile__ ("call _fail");


    // __asm__ __volatile__ ("ecall");

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}