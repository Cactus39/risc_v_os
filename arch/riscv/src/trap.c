#include <csr.h>
#include <soc.h>
#include <time.h>
#include <schedule.h>
#include <sys.h>

char const *mcause_sec[] = {
    [0] = "Instruction address misaligned",
    [1] = "Instruction access fault",
    [2] = "Illegal instruction",
    [3] = "Breakpoint",
    [4] = "Load address misaligned",
    [5] = "Load access fault",
    [6] = "Store/AMO address misaligned",
    [7] = "Store/AMO access fault",
    [8] = "Ecall from U-mode",
    [11] = "Ecall from M-mode",
    [12] = "Instruction page fault",
    [13] = "Load page fault",
    [15] = "Store/AMO page fault"
};
// extern void return_from_trap(void);

void log(unsigned int mepc,
    unsigned int mcause,
    unsigned int mtval,
    unsigned int mstatus){
    uprintf("\n[I] mepc %x\n", mepc);
    uprintf("[I] mcause %x %s\n", mcause, mcause_sec[mcause]);
    uprintf("[I] mtval %u\n", mtval);
    uprintf("[I] mstatus %u\n", mstatus);
}

registers_t *do_trap(registers_t *p){
    if (p->mcause == MCAUSE_EXCEPTION)
    {
        p->mepc += 4;
        if (p->regs[A7] == ECALL_SLEEP)
        {
            __sys_sleep_task((p->regs[A0]));
            return schedule(p);
        }
        if (p->regs[A7] == ECALL_EXIT) {
            __sys_exit(p->regs[A0]);
            return schedule(p);
        }

        return (p);
    }
    if (p->mcause & (MCAUSE_IRQ)) {  // interrupts (1 << 31)
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

