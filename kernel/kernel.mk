KERNEL_C_FILES = kernel/time/time.c kernel/schedule.c kernel/sys.c
KERNEL_S_FILES = kernel/ecalls.S
KERNEL_C_OBJS = $(KERNEL_C_FILES:.c=.o)
KERNEL_S_OBJS = $(KERNEL_S_FILES:.S=.o)

KERNEL_OBJS = $(KERNEL_C_OBJS) $(KERNEL_S_OBJS)
OBJS += $(KERNEL_OBJS)
HEADERS += includes
IHEADERS += -I includes