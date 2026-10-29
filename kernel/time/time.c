#include <soc.h>
#include <config.h>
#include <sys.h>

volatile unsigned int jiffies;
extern task_t *current;
void    tick_handler(void) {
    unsigned int next_tick = TICK_US;
    jiffies++;
    set_mtimecmp(next_tick);
}

void    msleep(unsigned int ms) {

    sys_sleep(jiffies + ((ms * HZ + 999)/1000));
}

unsigned int    uptime_ms(void) {
    return (jiffies * (1000 / (HZ)));
}
