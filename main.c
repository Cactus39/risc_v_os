struct regs {
    unsigned int regs[32];
    unsigned int mepc;
    unsigned int mcause;
    unsigned int mtval;
};

int     global_var = 1;
int     bss;
int     bss2 = 0;

void do_trap(struct regs *p) {

    if (p->mcause == 11) {
        p->mepc += 4;
        return ;
    }
    for (;;)
        ;

}
