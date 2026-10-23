
DRIVER_FILES = drivers/clk/clk.c drivers/reset/reset.c drivers/tty/uart.c
DRIVER_OBJS = $(DRIVER_FILES:.c=.o)
OBJS += $(DRIVER_OBJS)

HEADERS += include/soc
IHEADERS += -I include/soc