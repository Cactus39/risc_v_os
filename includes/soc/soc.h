#ifndef SOC_H
# define SOC_H

int     init_clk(void);
int     init_reset(void);
int     init_uart(void);
void    gpio_pad_set(int pin, int od, int ie);
int     gpio_io_set(int pin, int funcsel);
int     uprintf(const char *s, ...);
void    start_ticks(void);
void    set_mtimecmp(unsigned int ticks);



#endif
