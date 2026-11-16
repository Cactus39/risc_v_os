#include <soc.h>
#include <schedule.h>
#include <mem.h>

void    startup_init(int(f1)(void), int(f2)(void), int(f3)(void));

int     start_kernel(void) {


    startup_init(&init_clk, &init_reset, &init_uart);
    init_mem();
    add_task();
    start_ticks();
    start_tasks();

    while (1)
        __asm__ __volatile__ ("wfi");
}