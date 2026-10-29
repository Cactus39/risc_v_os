#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>
#include <schedule.h>


int     start_kernel(void) {
    __asm__ __volatile__ ("csrc mie, %0":: "r"(MIE_MTIE));

    init_clk();
    init_reset();
    init_uart();
    // udelay(100000);
    uprintf("\033c");
    uprintf("\033[32m[started]\033[0m\n");
    udelay(500000);
    add_task();

    start_ticks();
    // udelay(3000000);
    start_tasks();
    // __asm__ __volatile__ ("call _fail");


    // __asm__ __volatile__ ("ecall");

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}