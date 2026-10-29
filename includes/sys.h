#ifndef SYS_H
# define SYS_H
# define ECALL_SLEEP 11
# define ECALL_EXIT 60

/* CALL ONLY INT TRAP MACHINE MODE */

#include <schedule.h>
void    __sys_sleep_task(unsigned int ms);
int     __sys_exit(int exit_code);


/* SYSCALLS CAN BE CALLED FROM ANYWHERE */

void    sys_sleep(unsigned int ms);             // ecall 11
int     sys_exit(int exit_code);                // ecall 60

#endif