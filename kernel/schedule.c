#include <schedule.h>
#include <soc.h>
#include <time.h>
#include <sys.h>

static unsigned char stack[3][2048] __attribute__((aligned(16)));
static unsigned char idle_stack[512] __attribute__((aligned(16)));

task_t tasks[3];
task_t *current;
task_t idle_task;

void    fn_task_exit(void) {
    sys_exit(0);
    while (1)
        __asm__ ("wfi");
}

void    fn_task_idle(void) {
    while (1)
        __asm__ ("wfi");
}

registers_t *schedule(registers_t *frame) {
    static task_t      *last;
    current->sp = frame;

    if (current == &idle_task)
        current = last;
    last = current;
    current = current->next;

    while (current != last)
    {
        if ((current->status == TASK_SLEEPING) && (current->wake_at <= jiffies))
        {
            current->status = TASK_RUNNING;
            return (current->sp);
        }
        current = current->next;
    }
    if ((current->status == TASK_SLEEPING) && (current->wake_at <= jiffies))
    {
        current->status = TASK_RUNNING;
        return (current->sp);
    }
    current = current->next;
    while (current != last)
    {
        if (current->status == TASK_RUNNING)
            return (current->sp);
        current = current->next;
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
    registers->regs[RA] = (unsigned int)fn_task_exit;
    task->sp = registers;
}

void    t1(void) {
    // while (1) {
    for (int i = 0; i < 13; i++){
        uprintf("first \t%u\n", uptime_ms());
        msleep(10);
    }
}
void    t2(void) {
    // while (1) {
    for (int i = 0; i < 7; i++){
        uprintf("secon \t\t%u\n", uptime_ms());
        msleep(20);
    }
}
void    t3(void) {
    // while (1) {
    for (int i = 0; i < 4; i++){
        uprintf("third \t\t\t%u\n", uptime_ms());
        msleep(40);
    }
}

void    start_tasks(void) {
    create_task(&idle_task, idle_stack, 512, fn_task_idle);
    idle_task.wake_at = 0;
    idle_task.status = TASK_RUNNING;
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
