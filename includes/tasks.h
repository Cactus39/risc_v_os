#ifndef TASKS_H
# define TASKS_H
# include <csr.h>

typedef struct task_s {
    registers_t *sp;
} task_t;

registers_t *schedule(registers_t *frame);
void    start_tasks(void);
void    init_tasks(void);



#endif