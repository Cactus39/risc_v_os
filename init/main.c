#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>

void    init_tasks(void);


int     start_kernel(void) {
    init_clk();
    init_reset();
    init_uart();
    start_ticks();

    set_mtimecmp(1000000);
    __asm__ __volatile__ ("csrs mie, %0":: "r"(MIE_MTIE));
    __asm__ __volatile__ ("csrs mstatus, %0":: "r"(MSTATUS_MIE));
    // __asm__ __volatile__ ("ecall");
    // __asm__ __volatile__ ("call _fail");
    init_tasks();
    while (1) {

        // uprintf("\033c");

        uprintf("%d\n", uptime_ms());

        msleep(1000);
    }

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}