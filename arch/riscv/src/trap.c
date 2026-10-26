#include <csr.h>
#include <soc.h>
#include <time.h>
#include <tasks.h>

extern void return_from_trap(void);

void log(unsigned int mepc, unsigned int mcause, unsigned int mtval) {
    uprintf("\n[I] mepc %x\n", mepc);
    uprintf("[I] mcause %x\n", mcause);
    uprintf("[I] mtval %u\n", mtval);
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

