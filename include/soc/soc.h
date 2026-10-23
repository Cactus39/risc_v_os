#ifndef SOC_H
# define SOC_H

int     init_clk(void);
int     init_reset(void);
int     init_uart(void);
void    uart_test(char);

#endif
