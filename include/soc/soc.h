#ifndef SOC_H
# define SOC_H

int     init_clk(void);
int     init_reset(void);
int     init_uart(void);
void    gpio_pad_set(int pin, int od, int ie);
int     gpio_io_set(int pin, int funcsel);

int     uart_putchar(const unsigned char c);
int     uart_puts(const char *s);
int     uart_putnbr(int a);
int     uart_putaddr(unsigned int a);
int     uart_putnbr_h(unsigned int a);
int     uart_putnbr_u(const unsigned int a);
int     uprintf(const char *s, ...);
void    start_ticks(void);
void    set_mtimecmp(unsigned int tics);


#endif
