#include <regs.h>
#include <csr.h>

unsigned long long int  get_ticks(void) {
    unsigned int mtime = 0;
    unsigned long long int mtimeh = 0;
    unsigned int mtimeh_2 = 0;

    mtimeh = REG(MTIMEH);
    mtime = REG(MTIME);
    mtimeh_2 = REG(MTIMEH);
    while (mtimeh != mtimeh_2) {
        mtimeh = REG(MTIMEH);
        mtime = REG(MTIME);
        mtimeh_2 = REG(MTIMEH);
    }
    mtimeh = (mtimeh << 32) | mtime;
    return (mtimeh);
}

void    start_ticks(void) {
    unsigned long long int mtime64;
    REG(MTIMECMP) = 0xffffffff;
    REG(MTIMECMPH) = 0xffffffff;

    REG(TICKS_RISCV_CYCLES) &= ~0x1ff;
    REG(TICKS_RISCV_CYCLES) |= 0xc;
    REG(TICKS_RISCV_CTRL) |= 1;
    mtime64 = get_ticks();
    mtime64 += 100000;
    REG(MTIMECMP) = 0xffffffff;
    REG(MTIMECMPH) = mtime64 >> 32;
    REG(MTIMECMP) = ((mtime64 & 0xffffffff));
    __asm__ __volatile__ ("csrs mie, %0":: "r"(MIE_MTIE));
    __asm__ __volatile__ ("csrs mstatus, %0":: "r"(MSTATUS_MIE));
}

void set_mtimecmp(unsigned int ticks) {
    unsigned long long int mtime64;

    mtime64 = ((unsigned long long int)(REG(MTIMECMPH))<<32 ) | (REG(MTIMECMP));
    mtime64 += ticks;
    REG(MTIMECMP) = 0xffffffff;
    REG(MTIMECMPH) = mtime64 >> 32;
    REG(MTIMECMP) = ((mtime64 & 0xffffffff));
}

void    udelay(unsigned int us) {
    unsigned int start = ((unsigned int)get_ticks());
    while ((unsigned int)get_ticks() - start < us);
}


