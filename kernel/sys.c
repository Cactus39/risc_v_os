#include <schedule.h>
#include <time.h>

void    __sys_sleep_start(unsigned int ms, task_t *current) {
    current->status = TASK_SLEEPING;
    current->wake_at = jiffies + ms;
}