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
    [9] = "Unknown",
    [10] = "Unknown",
    [11] = "Ecall from M-mode",
    [12] = "Instruction page fault",
    [13] = "Load page fault",
    [15] = "Store/AMO page fault"
};

void kernel_panic(unsigned int mepc,
    unsigned int mcause,
    unsigned int mtval,
    unsigned int mstatus){
    irq_disable();
    uprintf("----------------------------------------------------------------\n");
    uprintf("Kernel panic\n");
    uprintf("\033[31m[ERROR]\033[0m mepc\t%x\n"
            "\033[31m[ERROR]\033[0m mcause\t%x\t%s\n"
            "\033[31m[ERROR]\033[0m mtval\t%u\n"
            "\033[31m[ERROR]\033[0m mstatus\t%x\n",
            mepc,
            mcause,
            mcause_sec[mcause < 16 ? mcause : 9],
            mtval,
            mstatus);
    uprintf("----------------------------------------------------------------\n");
}

registers_t *do_syscall(registers_t *p) {
    if (p->regs[A7] == ECALL_SLEEP)
        __sys_sleep_task((p->regs[A0]));
    else if (p->regs[A7] == ECALL_EXIT)
        __sys_exit(p->regs[A0]);
    else
        return (p);
    return schedule(p);
}

registers_t *do_trap(registers_t *p){
    if (p->mcause == MCAUSE_EXCEPTION)
    {
        p->mepc += 4;
        p = do_syscall(p);
        return (p);
    }
    if (p->mcause & (MCAUSE_IRQ)) {  // interrupts (1 << 31)
        if ((p->mcause & ~(MCAUSE_IRQ)) == MCAUSE_MTIRQ)
        {
            tick_handler();
            return (schedule(p));
        }
        return (p);
    }
    kernel_panic(p->mepc, p->mcause, p->mtval, p->mstatus);
    for (;;)
        __asm__ __volatile__ ("wfi");
}

