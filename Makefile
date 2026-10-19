.PHONY: all re clean flash objdump fclean connect

NAME = init.elf
FILES = init.S
S_OBJS = $(FILES:.S=.o)
OBJS = $(S_OBJS)
all: $(NAME)

$(NAME): $(OBJS)
	riscv64-unknown-elf-ld -m elf32lriscv -T memmap.ld $(OBJS) -o $@

%.o: %.S
	riscv64-unknown-elf-gcc -g -march=rv32imac_zicsr_zifencei -mabi=ilp32 -c $< -o $@

objdump:
	riscv64-unknown-elf-objdump -d $(NAME)

flash:
	openocd -f interface/cmsis-dap.cfg -f target/rp2350-riscv.cfg -c "adapter speed 5000" -c "program $(NAME) verify reset exit"
connect:
	openocd -f interface/cmsis-dap.cfg -f target/rp2350-riscv.cfg -c "adapter speed 5000"

clean:
	rm -rf *.o
fclean: clean
	rm -rf $(NAME)
re: fclean all