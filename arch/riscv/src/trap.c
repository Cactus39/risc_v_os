#include <csr.h>
#include <soc.h>
#include <time.h>
#include <schedule.h>
#include <sys.h>

// extern void return_from_trap(void);
extern task_t *current;
void log(unsigned int mepc,
    unsigned int mcause,
    unsigned int mtval,
    unsigned int mstatus){
    uprintf("\n[I] mepc %x\n", mepc);
    uprintf("[I] mcause %x\n", mcause);
    uprintf("[I] mtval %u\n", mtval);
    uprintf("[I] mstatus %u\n", mstatus);
}

registers_t *do_trap(registers_t *p){
    if (p->mcause == MCAUSE_EXCEPTION)
    {
        p->mepc += 4;
        if (p->regs[A7] == ECALL_SLEEP)
        {
            __sys_sleep_start((p->regs[A0]), current);
            return schedule(p);
        }
        return (p);
    }
    if (p->mcause & (MCAUSE_IRQ)) {  // interrupts
        if ((p->mcause & 0x7) == MCAUSE_MTIRQ)  // machine timer interrupt
        {
            tick_handler();
            return (schedule(p));
        }
        return (p);
    }
    log(p->mepc, p->mcause, p->mtval, p->mstatus);
    for (;;)
        ;
}

