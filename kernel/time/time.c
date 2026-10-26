#include <soc.h>
#include <config.h>
// #include <time.h>

volatile unsigned int jiffies;

void    tick_handler(void) {
    unsigned int next_tick = TICK_US;
    jiffies++;
    set_mtimecmp(next_tick);
}

void    msleep(unsigned int ms) {
    unsigned int end = jiffies + ((ms * HZ + 999)/1000);
    while (jiffies < end)
        __asm__ __volatile__ ("wfi");
}

unsigned int    uptime_ms(void) {
    return (jiffies * (1000 / HZ));
}
