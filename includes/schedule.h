#ifndef SCHEDULE_H
# define SCHEDULE_H
# include <csr.h>

enum task_status_t{
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_DEAD,
    TASK_ERROR
};

typedef struct task_s{
    registers_t         *sp;
    enum task_status_t    status;
    unsigned int        wake_at;
    struct task_s       *next;
} task_t;

registers_t     *schedule(registers_t *frame);
void            start_tasks(void);
void            add_task(void);



#endif