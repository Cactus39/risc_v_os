
DRIVER_FILES = drivers/clk/clk.c drivers/reset/reset.c drivers/tty/uart.c\
				drivers/pinctrl/pinctrl.c drivers/clocksource/riscv_timer.c
DRIVER_OBJS = $(DRIVER_FILES:.c=.o)
OBJS += $(DRIVER_OBJS)

HEADERS += includes/soc
IHEADERS += -I includes/soc