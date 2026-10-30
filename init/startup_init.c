#include <config.h>

extern int uart_puts(const char *s);
extern int uart_putnbr(int a);
extern int uart_putaddr(unsigned int a);

void    startup_log(int cond, char *msg, unsigned int val) {
    char    *ko_msg = "\n\033[31m[KO]\t\033[0m";
    char    *ok_msg = "\n\033[32m[OK]\t\033[0m";
    uart_puts(cond ? ok_msg : ko_msg);
    uart_puts(msg);
    if (val < 0x10000000)
        uart_putnbr(val);
    else
        uart_putaddr(val);
}

void    startup_init(int(f1)(void), int(f2)(void), int(f3)(void)) {
    unsigned int    mem[9];
    int             status[3];

    __asm__ __volatile ("csrr   %0, mhartid":"=r"(mem[6]));
    __asm__ __volatile ("la %0, __stack_top":"=r"(mem[0]));
    __asm__ __volatile ("mv %0, sp":"=r"(mem[1]));
    __asm__ __volatile ("la %0, __data_start":"=r"(mem[2]));
    __asm__ __volatile ("la %0, __data_end":"=r"(mem[3]));
    __asm__ __volatile ("la %0, __bss_start":"=r"(mem[4]));
    __asm__ __volatile ("la %0, __bss_end":"=r"(mem[5]));
    __asm__ __volatile ("la %0, __heap_start":"=r"(mem[7]));
    __asm__ __volatile ("la %0, __heap_end":"=r"(mem[8]));

    status[0] = f1();
    status[1] = f2();
    status[2] = f3();
    uart_puts("\033c");
    startup_log(mem[6] == 0x0, "CORE ID\t\t", mem[6]);
    startup_log(mem[2] == 0x20000000, ".DATA START\t", mem[2]);
    startup_log(!(mem[3] & 0x3), ".DATA END\t", mem[3]);
    startup_log(((mem[4] >= mem[3]) & !(mem[4] & 0x3)), ".BSS START\t", mem[4]);
    startup_log((!(mem[5] & 0x3)), ".BSS END\t", mem[5]);
    startup_log((!(mem[7] & 0x3)), ".HEAP START\t", mem[7]);
    startup_log((!(mem[8] & 0x3)), ".HEAP END\t", mem[8]);
    startup_log(mem[0] == 0x20080000, "STACK TOP\t", mem[0]);
    startup_log(mem[1] <= mem[0] && mem[1] > mem[8] && !(mem[1] & 0xf),
        "[SP]\t\t",
        mem[1]);
    startup_log(((mem[8] - mem[7]) / PAGE_SHIFT == MAX_ORDER),
        "PAGES\t\t",
        (mem[8] - mem[7]) / PAGE_SHIFT);
    startup_log(!status[0], "CLOCK\t\t", status[0]);
    startup_log(!status[1], "RESETS\t\t", status[1]);
    startup_log(!status[2], "UART\t\t", status[2]);
    uart_puts("\n\n");
}