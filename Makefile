.PHONY: all re clean flash objdump fclean connect
NAME = init.elf
MEMMAP = arch/kernel/src/memmap.ld
C_FILES = main.c

OBJS = $(C_FILES:.c=.o)
HEADERS =
include arch/kernel/kernel.mk

GCC_FLAGS = -c -g -march=rv32imac_zicsr_zifencei -mabi=ilp32 -Wall -Wextra -Werror
GCC_FLAGS_C = -ffreestanding -mstrict-align -fno-pic -Os -msmall-data-limit=0
all: $(NAME)

$(NAME): $(OBJS) $(MEMMAP) $(HEADERS)
	riscv64-unknown-elf-ld -g -m elf32lriscv -T $(MEMMAP) $(OBJS) -o $@

%.o:%.S
	riscv64-unknown-elf-gcc $(GCC_FLAGS) $< -o $@
%.o:%.c
	riscv64-unknown-elf-gcc -I $(HEADERS) $(GCC_FLAGS_C) $(GCC_FLAGS) $< -o $@
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