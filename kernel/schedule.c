#include <schedule.h>
#include <soc.h>
#include <time.h>


static unsigned char stack[3][2048] __attribute__((aligned(16)));
static unsigned char idle_stack[512] __attribute__((aligned(16)));

task_t tasks[3];
task_t *current;
task_t idle_task;  // = {
    // .sp = (registers_t*)((idle_stack + 512) - 144),
    // .status = TASK_RUNNING,
    // .wake_at = 0
// };

void    task_exit(void) {
    while (1)
        __asm__ ("wfi");
}

task_t *next_task(task_t *t) {
    if (t >= &tasks[2])
        t = &tasks[0];
    else
        t++;
    return t;
}

registers_t *schedule(registers_t *frame) {
    static task_t      *last;
    current->sp = frame;

    if (current == &idle_task)
        current = last;
    last = current;
    current = next_task(current);

    while (current != last)
    {
        if ((current->status == TASK_SLEEPING) && (current->wake_at <= jiffies))
        {
            current->status = TASK_RUNNING;
            return (current->sp);
        }
        current = next_task(current);
    }
    if ((current->status == TASK_SLEEPING) && (current->wake_at <= jiffies))
    {
        current->status = TASK_RUNNING;
        return (current->sp);
    }
    current = next_task(current);
    while (current != last)
    {
        if (current->status == TASK_RUNNING)
            return (current->sp);
        current = next_task(current);
    }
    if (current->status == TASK_RUNNING)
        return (current->sp);
    /* 0 i a 0 0 1 */
    current = &idle_task;
    return (idle_task.sp);

}

void    create_task(task_t *task, unsigned char *stack, unsigned int size, void(*fn)(void)) {
    unsigned int    top = (unsigned int)(stack + size) & ~0xf;

    registers_t *registers = (registers_t *)(top - 144);
    for (int i = 0; i < 144 / 4; i++)
        ((unsigned int *)registers)[i] = 0;
    registers->mepc = (unsigned int)fn;
    registers->regs[RA] = (unsigned int)task_exit;
    task->sp = registers;
}

void    t1(void) {
    while (1) {
        uprintf("first %u\n", uptime_ms());
        msleep(1000);
    }
}
void    t2(void) {
    while (1) {
        uprintf("second %u\n", uptime_ms());
        msleep(2000);
    }
}
void    t3(void) {
    while (1) {
        uprintf("third %u\n", uptime_ms());
        msleep(4000);
    }
}

void    start_tasks(void) {

    idle_task.sp = (registers_t *)(((unsigned int)(idle_stack + 512) & ~(0xf)) - 144);
    for (int i = 0; i < 144 / 4; i++)
        ((unsigned int *)idle_task.sp)[i] = 0;
    idle_task.status = TASK_RUNNING;
    idle_task.wake_at = 0;
    idle_task.sp->mepc = (unsigned int)task_exit;
    idle_task.sp->regs[RA] = (unsigned int)task_exit;
    __asm__ __volatile__ ("csrs mstatus, %0":: "r"(MSTATUS_MPP | MSTATUS_MPIE));
    __asm__ __volatile__ ("mv sp, %0\n\t"
                            "j ret_from_trap":: "r"(current->sp));
}
void    add_task(void) {
    create_task(&tasks[0], stack[0], 2048, t1);
    tasks[0].next = &tasks[1];
    create_task(&tasks[1], stack[1], 2048, t2);
    tasks[1].next = &tasks[2];
    create_task(&tasks[2], stack[2], 2048, t3);
    tasks[2].next = &tasks[0];


    current = &tasks[0];
}

// void    sys_sleep(unsigned int ms) {
//     current->status = TASK_SLEEPING;
//     current->wake_at = p->regs[A0];
//
// }