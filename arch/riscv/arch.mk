ARCH_S_FILES = arch/riscv/src/init.S arch/riscv/src/entry.S\
 				arch/riscv/src/image.S arch/riscv/src/csr.S
ARCH_C_FILES = arch/riscv/src/trap.c

ARCH_S_OBJS = $(ARCH_S_FILES:.S=.o)
ARCH_C_OBJS = $(ARCH_C_FILES:.c=.o)
ARCH_OBJS = $(ARCH_S_OBJS) $(ARCH_C_OBJS)

OBJS += $(ARCH_OBJS)
HEADERS += arch/riscv/include
IHEADERS += -I arch/riscv/include