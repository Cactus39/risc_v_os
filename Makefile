.PHONY: all re clean flash objdump fclean connect

NAME = init.elf
MEMMAP = arch/riscv/src/memmap.ld
S_FILES = arch/riscv/src/init.S arch/riscv/src/entry.S arch/riscv/src/image.S
C_FILES = arch/riscv/src/trap.c main.c
S_OBJS = $(S_FILES:.S=.o)
C_OBJS = $(C_FILES:.c=.o)
OBJS = $(S_OBJS) $(C_OBJS)
GCC_FLAGS = -c -g -march=rv32imac_zicsr_zifencei -mabi=ilp32
GCC_FLAGS_C = -ffreestanding -mstrict-align -fno-pic -Os -msmall-data-limit=0
all: $(NAME)

$(NAME): $(OBJS) $(MEMMAP)
	riscv64-unknown-elf-ld -m elf32lriscv -T $(MEMMAP) $(OBJS) -o $@

%.o:%.S
	riscv64-unknown-elf-gcc $(GCC_FLAGS) $< -o $@
%.o:%.c
	riscv64-unknown-elf-gcc $(GCC_FLAGS_C) $(GCC_FLAGS) $< -o $@
objdump:
	riscv64-unknown-elf-objdump -d $(NAME)

flash:
	openocd -f interface/cmsis-dap.cfg -f\
	target/rp2350-riscv.cfg -c "adapter speed 5000" -c "program $(NAME) verify reset exit"
connect:
	openocd -f interface/cmsis-dap.cfg -f target/rp2350-riscv.cfg -c "adapter speed 5000"

clean:
	rm -rf *.o && rm -rf */*/*/*.o
fclean: clean
	rm -rf $(NAME)
re: fclean all