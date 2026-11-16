#ifndef SCHEDULE_H
# define SCHEDULE_H
// #include "../../arch/riscv/include/csr.h"
// # include <csr.h>

enum task_status_t{
    TASK_RUNNING,
    TASK_DEAD,
    TASK_SLEEPING,
    TASK_ERROR
};
typedef struct registers_s registers_t;
typedef struct page_s page_t;
typedef struct task_s{
    registers_t         *sp;
    struct task_s       *next;
	page_t				*page;
    unsigned int        id;
    unsigned int        mem;
    unsigned int        wake_at;
    enum task_status_t  status;
} task_t;

registers_t     *schedule(registers_t *frame);
void	        start_tasks(void);
void			add_task(void);

#endif