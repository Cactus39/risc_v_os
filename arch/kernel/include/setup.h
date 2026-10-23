#ifndef SETUP_H
# define SETUP_H

# define REG(a) (*(volatile unsigned int *)(a))
# define RESET_BASE 0x40020000UL
# define RESET_DONE 0x40020008Ul

# define RES_UART0_BIT 1 << 26
# define RES_PADS_BANK0_BIT 1 << 9
# define RES_IO_BANK0_BIT 1 << 6

# define XOSC_BASE 0x40048000UL
# define XOSC_ENABLE 0xfab
# define XOSC_DISABLE 0xd1e
# define XOSC_FREQ_1_15 0xaa0

# define XOSC_STATUS 0x40048004UL
# define XOSC_STATUS_STABLE 1 << 31
# define XOSC_STATUS_ENABLED 1 << 12
# define XOSC_STATUS_BADWRITE 1 << 24

# define CLK_BASE 0x40010000UL
# define CLK_REF_CTRL 0x40010030UL
# define ROSC_CLKSRC 0x0
# define XOSC_CLKSRC 0x2
# define CLK_REF_SELECTED 0x40010038
# define CLK_REF_XOSC_SELECTED 1 << 2

# define CLK_SYS_CTRL 0x4001003cUL
# define CLK_SYS_SELECTED 0x40010044UL

# define CLK_PERI_CTRL 0x40010048UL
# define CLK_PERI_ENABLED 1 << 28
# define CLK_PERI_ENABLE 1 << 11
# define CLK_AUXSRC(a) ((a)<<(5))
# define CLK_PERI_DIV 0x4001004cUL /*1 << 16*/



# define UART0_BASE 0x40070000UL
# define UART_PERIPHID0 0xfe0
# define UART_PCELLID0 0xff0


#endif