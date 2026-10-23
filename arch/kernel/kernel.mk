KERNEL_S_FILES = arch/kernel/src/init.S arch/kernel/src/entry.S arch/kernel/src/image.S
KERNEL_C_FILES = arch/kernel/src/trap.c arch/kernel/src/setup.c

KERNEL_S_OBJS = $(KERNEL_S_FILES:.S=.o)
KERNEL_C_OBJS = $(KERNEL_C_FILES:.c=.o)
KERNEL_OBJS = $(KERNEL_S_OBJS) $(KERNEL_C_OBJS)

OBJS += $(KERNEL_OBJS)
HEADERS += arch/kernel/include