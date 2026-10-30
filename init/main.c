#include <soc.h>
#include <regs.h>
#include <csr.h>
#include <time.h>
#include <schedule.h>

void    startup_init(int(f1)(void), int(f2)(void), int(f3)(void));

int     start_kernel(void) {


    startup_init(&init_clk, &init_reset, &init_uart);
    add_task();
    start_ticks();
    start_tasks();
    // __asm__ __volatile__ ("call _fail");
    // __asm__ __volatile__ ("ecall");

    for (;;) {
        __asm__ __volatile__ ("nop" ::: "memory");
    }
}