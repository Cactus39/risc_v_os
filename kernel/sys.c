#include <schedule.h>
// #include <time.h>

extern task_t *current;

/* CALL ONLY IN TRAP MACHINE MODE */

void    __sys_sleep_task(unsigned int wake) {
    current->status = TASK_SLEEPING;
    current->wake_at = wake;
}

int __sys_exit(int exit_code) {
    if (!exit_code)
        current->status = TASK_DEAD;
    else
        current->status = TASK_ERROR;
    return (exit_code);
}