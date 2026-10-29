#ifndef CSR_H
# define CSR_H

void    _fail(void);
typedef struct registers_s {
    unsigned int regs[32];
    unsigned int mepc;
    unsigned int mcause;
    unsigned int mtval;
    unsigned int mstatus;
} registers_t;

/* registers macs */
# define RA 01
# define SP 02
# define A0 10
# define A1 11
# define A2 12
# define A3 13
# define A4 14
# define A5 15
# define A6 16
# define A7 17


/* mie mip bits*/
#define MIE_MTIE (1 << 7)  // Machine Timer Interrupt Enable
#define MIP_MTIP (1 << 7)  // Machine Timer Interrupt Pending
#define MIE_MSIE (1 << 3)  // Machine Software Interrupt Enable
#define MIP_MSIP (1 << 3)  // Machine Software Interrupt Pending
#define MIE_MEIE (1 << 11)  // Machine External Interrupt Enable
#define MIP_MEIP (1 << 11)  // Machine External Interrupt Pending

/* mstatus bits */
# define MSTATUS_MIE (1 << 3)  // Machine Interrupt Enable
# define MSTATUS_MPIE (1 << 7)  // Machine Previous Interrupt Enable
# define MSTATUS_MPP (3 << 11)  // Machine Previous Privelege

/* mcause macs */
# define MCAUSE_EXCEPTION 11
# define MCAUSE_IRQ (1u << 31)
# define MCAUSE_MTIRQ 7
# define MCAUSE_T

#endif