#include <schedule.h>
#include <time.h>

/* CALL ONLY INT TRAP MACHINE MODE */
extern task_t *current;

void    __sys_sleep_task(unsigned int ms) {
    current->status = TASK_SLEEPING;
    current->wake_at = jiffies + ms;
}

int __sys_exit(int exit_code) {
    if (!exit_code)
        current->status = TASK_DEAD;
    else
        current->status = TASK_ERROR;
    return (exit_code);
}