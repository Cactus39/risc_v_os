KERNEL_S_FILES = arch/riscv/src/init.S arch/riscv/src/entry.S arch/riscv/src/image.S
KERNEL_C_FILES = arch/riscv/src/trap.c

KERNEL_S_OBJS = $(KERNEL_S_FILES:.S=.o)
KERNEL_C_OBJS = $(KERNEL_C_FILES:.c=.o)
KERNEL_OBJS = $(KERNEL_S_OBJS) $(KERNEL_C_OBJS)

OBJS += $(KERNEL_OBJS)
HEADERS += arch/riscv/include
IHEADERS += -I arch/riscv/include