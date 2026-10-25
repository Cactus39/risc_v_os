#include <soc.h>

struct regs {
    unsigned int regs[32];
    unsigned int mepc;
    unsigned int mcause;
    unsigned int mtval;
};

void log(unsigned int mepc, unsigned int mcause, unsigned int mtval) {
    uprintf("[Error] mepc %p\n", mepc);
    uprintf("[Error] mcause %p\n", mcause);
    uprintf("[Error] mtval %u\n", mtval);
}
void do_trap(struct regs *p) {
    if (p->mcause == 11) {
        log(p->mepc, p->mcause, p->mtval);
        p->mepc += 4;
        return ;
    }
    static int counter = 0;
    if (p->mcause & 0x80000000) {
        uprintf("%d\n", counter++);
        log(p->mepc, p->mcause, p->mtval);
        if ((p->mcause & 0x7fffffff) == 7)
            set_mtimecmp(1000000);
        return ;
    }

    for (;;)
        ;
}

