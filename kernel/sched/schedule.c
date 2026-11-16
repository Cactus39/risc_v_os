#include <schedule.h>
#include <soc.h>
#include <time.h>
#include <sys.h>
#include <csr.h>
#include <mem.h>
#include <config.h>

task_t tasks[3];
task_t *current;
task_t idle_task;

void    fn_task_exit(void) {
	check_mem();
    sys_exit(0);
    uprintf("\n\033[31m[ERROR]\033[0m task %p running after exit\n", &current);
    while (1)
        __asm__ ("wfi");
}

void    fn_task_idle(void) {
    while (1)
        __asm__ ("wfi");
}

int    time_to_wake(task_t *c) {
    if ((c->status == TASK_SLEEPING) && !TIME_AFTER(c->wake_at, jiffies))
        return (1);
    return (0);
}

registers_t *schedule(registers_t *frame) {
    static task_t      *last;
    current->sp = frame;

    if (current->next)
        last = current;
    else
        current = last;
    current = current->next;
    while (current != last)
    {
        if (time_to_wake(current))
            current->status = TASK_RUNNING;
    	if (current->next->status == TASK_DEAD && current->next->page)
    	{
    		free_pages(current->next->page, 1);
    		current->next->page = NULL;
    	}
        current = current->next;
    }
    if (time_to_wake(current))
        current->status = TASK_RUNNING;
    current = current->next;
    while (current != last)
    {
        if (current->status == TASK_RUNNING)
            return (current->sp);
        current = current->next;
    }
    if (current->status == TASK_RUNNING)
        return (current->sp);
    current = &idle_task;
    return (idle_task.sp);
}

page_t	*create_task(task_t *task, unsigned int size, void(*fn)(void)) {
	page_t			*page = alloc_pages(1);
	if (page == NULL)
		return (NULL);
	unsigned char	*stack = (unsigned char *)(RAM_START + (page->index * PAGE_SIZE));
    unsigned int	csr_flags = (MSTATUS_MPP | MSTATUS_MPIE);
    unsigned int    top = (unsigned int)(stack + size) & ~0xf;

    registers_t *registers = (registers_t *)(top - 144);
    for (int i = 0; i < 144 / 4; i++)
        ((unsigned int *)registers)[i] = 0;
    registers->mepc = (unsigned int)fn;
    registers->mstatus = csr_flags;
    registers->regs[RA] = (unsigned int)fn_task_exit;
    task->sp = registers;
	return (page);
}

void    t1(void) {
    for (int i = 0; i < 9; i++){
        uprintf("\n %d", uptime_ms());
        msleep(1000);
    }
    // _fail();
}
void    t2(void) {
    for (int i = 0; i < 5; i++){
        uprintf("\t%d", uptime_ms());
        msleep(2000);
    }
}
void    t3(void) {
    for (int i = 0; i < 3; i++){
    //while (1){
        uprintf("\t\t%d", uptime_ms());
        msleep(4000);
    }
}

void    start_tasks(void) {
	idle_task.mem = 2048;
    idle_task.page = create_task(&idle_task, idle_task.mem, fn_task_idle);
	if (idle_task.page == NULL)
		return ;
    idle_task.wake_at = 0;
    idle_task.id = 0;
    idle_task.status = TASK_RUNNING;
    idle_task.next = (void *)0;
    current = &tasks[0];
    __asm__ __volatile__ ("mv sp, %0\n\t"
                            "j ret_from_trap":: "r"(current->sp));
}

void    add_task(void) {
	tasks[0].mem = 2048;
    tasks[0].page = create_task(&tasks[0], tasks[0].mem, t1);
	if (tasks[0].page == NULL)
		return ;
    tasks[0].status = TASK_RUNNING;
    tasks[0].id = 1;
    tasks[0].next = &tasks[1];
	tasks[1].mem = 2048;
    tasks[1].page = create_task(&tasks[1], tasks[1].mem, t2);
	if (tasks[1].page == NULL)
		return ;
    tasks[1].status = TASK_RUNNING;
    tasks[1].id = 2;
    tasks[1].next = &tasks[2];
	tasks[2].mem = 2048;
    tasks[2].page = create_task(&tasks[2], tasks[2].mem, t3);
	if (tasks[2].page == NULL)
		return ;
    tasks[2].status = TASK_RUNNING;
    tasks[2].id = 3;
    tasks[2].next = &tasks[0];

}
