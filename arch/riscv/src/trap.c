#include <csr.h>
#include <soc.h>
#include <time.h>

extern void return_from_trap(void);

// typedef struct registers_s {
//     unsigned int regs[32];
//     unsigned int mepc;
//     unsigned int mcause;
//     unsigned int mtval;
// } registers_t;

// typedef struct task_s {
//      registers_t *sp;
// } task_t;

void log(unsigned int mepc, unsigned int mcause, unsigned int mtval) {
    uprintf("\n[I] mepc %x\n", mepc);
    uprintf("[I] mcause %x\n", mcause);
    uprintf("[I] mtval %u\n", mtval);
}

static unsigned char stack[3][2048] __attribute__((aligned(16)));

task_t tasks[3];
task_t *current;

void    task_exit(void) {
    for (;;)
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
     current->sp = frame;
     current = next_task(current);
     return (current->sp);
}

void    create_task(task_t *task, unsigned char *stack, unsigned int size, void(*fn)(void)) {
    unsigned int top = (unsigned int)(stack + size) & ~0xf;
    registers_t *registers = (registers_t *)(top - 144);
    for (int i = 0; i < 144 / 4; i = i + 4)
        ((unsigned int *)registers)[i] = 0;
    registers->mepc = (unsigned int)fn;
    registers->regs[1] = (unsigned int)task_exit;
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
    uprintf("third\n");
}

void    start_tasks(void) {
    __asm__ __volatile__ ("csrs mstatus, %0":: "r"(MSTATUS_MPP | MSTATUS_MPIE));
    __asm__ __volatile__ ("mv sp, %0\n\t"
                            "j ret_from_trap":: "r"(current->sp));
}
void    init_tasks(void) {
    create_task(&tasks[0], stack[0], 2048, t1);
    create_task(&tasks[1], stack[1], 2048, t2);
    create_task(&tasks[2], stack[2], 2048, t3);
    // __asm__ __volatile__ ("csrs mstatus, %0":: "r"(MSTATUS_MPP | MSTATUS_MPIE));
    current = &tasks[0];
    // __asm__ __volatile__ ("mv sp, %0\n\t"
    //                         "j ret_from_trap":: "r"(current->sp));
}
registers_t *do_trap(registers_t *p) {
    if (p->mcause == 11) {
        p->mepc += 4;
        return (p);
    }
    if (p->mcause & (1u << 31)) {  // interrupts
        if ((p->mcause & ~(1u << 31)) == 7) {
            tick_handler();
            return (schedule(p));
        }
        return (p);
    }
    log(p->mepc, p->mcause, p->mtval);
    for (;;)
        ;
}

