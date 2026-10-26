KERNEL_FILES = kernel/time/time.c
KERNEL_OBJS = $(KERNEL_FILES:.c=.o)

OBJS += $(KERNEL_OBJS)
HEADERS += includes
IHEADERS += -I includes