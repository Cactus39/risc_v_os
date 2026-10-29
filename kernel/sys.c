#include <schedule.h>
#include <time.h>
#include <config.h>

extern task_t *current;

/* CALL ONLY IN TRAP MACHINE MODE */

void    __sys_sleep_task(unsigned int ms) {
    current->status = TASK_SLEEPING;
    current->wake_at = jiffies + ((ms * HZ + 999)/1000);
}

int __sys_exit(int exit_code) {
    if (!exit_code)
        current->status = TASK_DEAD;
    else
        current->status = TASK_ERROR;
    return (exit_code);
}