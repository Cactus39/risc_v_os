#include <soc.h>
#include <config.h>
#include <sys.h>

volatile unsigned int jiffies;
extern task_t *current;
extern unsigned long long int  get_ticks(void);

void    tick_handler(void) {
    unsigned int next_tick = TICK_US;
    jiffies++;
    set_mtimecmp(next_tick);
}

void    msleep(unsigned int ms) {
    sys_sleep(ms);
}

unsigned int    uptime_ms(void) {
    return (jiffies * (1000 / (HZ)));
}

void    udelay(unsigned int us) {
    unsigned int start = ((unsigned int)get_ticks());
    while ((unsigned int)get_ticks() - start < us);
}


