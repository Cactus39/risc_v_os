
extern int uart_puts(const char *s);
extern int uart_putnbr(int a);
extern int uart_putaddr(unsigned int a);

void    startup_log(int cond, char *msg, unsigned int val) {
    char    *ko_msg = "\n\033[31m[KO]\t\033[0m";
    char    *ok_msg = "\n\033[32m[OK]\t\033[0m";
    uart_puts(cond ? ok_msg : ko_msg);
    uart_puts(msg);
    if (val != 0)
        uart_putaddr(val);
    else
        uart_putnbr(val);
}

void    startup_init(int(f1)(void), int(f2)(void), int(f3)(void)) {
    unsigned int mem[6];
    int     status[3];

    __asm__ __volatile ("la %0, __stack_top":"=r"(mem[0]));
    __asm__ __volatile ("la %0, __data_start":"=r"(mem[2]));
    __asm__ __volatile ("la %0, __data_end":"=r"(mem[3]));
    __asm__ __volatile ("la %0, __bss_start":"=r"(mem[4]));
    __asm__ __volatile ("la %0, __bss_end":"=r"(mem[5]));
    __asm__ __volatile ("csrr   %0, mhartid":"=r"(mem[1]));
    status[0] = f1();
    status[1] = f2();
    status[2] = f3();
    uart_puts("\033c");
    startup_log(mem[1] == 0x0, "CORE ID\t\t", mem[1]);
    startup_log(mem[2] == 0x20000000, ".DATA START\t", mem[2]);
    startup_log(!(mem[3] & 0x3), ".DATA END\t", mem[3]);
    startup_log(((mem[4] >= mem[3]) & !(mem[4] & 0x3)), ".BSS START\t", mem[4]);
    startup_log((!(mem[5] & 0x3)), ".BSS END\t", mem[5]);
    startup_log(mem[0] == 0x20080000, "STACK TOP ON\t", mem[0]);
    startup_log(!status[0], "CLOCK\t\t", status[0]);
    startup_log(!status[1], "RESETS\t\t", status[1]);
    startup_log(!status[2], "UART\t\t", status[2]);
    uart_puts("\n\n");
}