#ifndef SYS_H
# define SYS_H
# define ECALL_SLEEP 11

#include <schedule.h>
void    __sys_sleep(unsigned int ms);
void    __sys_sleep_start(unsigned int ms, task_t *current);

#endif