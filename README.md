# risc_v_os

A small Linux-inspired kernel for the **Raspberry Pi Pico 2 W (RP2350, RISC-V Hazard3 core)**,
written from scratch in C and RISC-V assembly: bare metal, **no Pico SDK, no libc**.
Flashed and debugged over SWD (Raspberry Pi Debug Probe, OpenOCD + gdb).

## Status

- [x] Boot: PICOBIN `IMAGE` block, `_start`, stack, `.bss` zeroing, `.data` copy from flash to SRAM
- [x] Linker script (`.data` has VMA in SRAM and LMA in flash)
- [x] Machine-mode trap entry/exit: full register frame, `mcause` / `mepc` / `mtval`.
- [x] Clock init: XOSC (12 MHz) -> `clk_ref` / `clk_sys` / `clk_peri`
- [x] Reset controller, pads and IO mux, PL011 UART0 driver
- [x] `uprintf`: own formatter (`%d %u %x %s %c`), no libc
- [x] Timer interrupt (`mtime` / `mtimecmp`, RISC-V tick generator), `jiffies`, `msleep()`, `uptime_ms()`
- [x] Preemptive round-robin scheduler: 3 kernel threads with separate stacks, switched from the timer interrupt
- [ ] Sleeping tasks (blocked state, wake-up time) instead of busy `msleep`
- [ ] Memory allocator
- [ ] UART ring buffer + TX interrupt / DMA, `printk` with log levels
- [ ] UART shell
- [ ] User mode: PMP, `mscratch` kernel stack, syscalls via `ecall`
- [ ] Filesystem, DVI output, compiler

## Hardware and tools

| | |
|---|---|
| Board | Raspberry Pi Pico 2 W (RP2350), Hazard3 RISC-V core, 512 KiB SRAM, XIP flash |
| Probe | Raspberry Pi Debug Probe (CMSIS-DAP, SWD) |
| Toolchain | `riscv64-unknown-elf-gcc` / `ld` (`rv32imac_zicsr_zifencei`, `ilp32`) |
| Debug | Raspberry Pi fork of OpenOCD (RP2350 support), `gdb-multiarch` |

## Build and flash

```sh
make            # builds init.elf
make flash      # programs the chip over SWD and resets it
make connect    # starts an OpenOCD server for gdb
```

UART0 output (115200 8N1) shows the uptime and the messages of the three tasks.

## Memory map

| Region | Address | Use |
|---|---|---|
| Boot ROM | `0x00000000` | RP2350 boot code (read-only) |
| XIP flash | `0x10000000` | `.MBR` (IMAGE_DEF), `.text`, `.rodata`, load image of `.data` |
| SRAM | `0x20000000` (512 KiB) | `.data`, `.bss`, task stacks, kernel stack (top of SRAM) |


## Repository layout

```
arch/riscv/      boot (init.S, image.S), trap entry (entry.S, trap.c), CSR helpers, linker script
drivers/clk/     XOSC and clock tree
drivers/reset/   RESETS block
drivers/pinctrl/ pads and IO mux
drivers/tty/     PL011 UART and uprintf
drivers/clocksource/  RISC-V tick generator, mtime / mtimecmp
kernel/          scheduler, jiffies, msleep
init/            start_kernel()
config/          HZ and other compile-time options
```

## References

- RP2350 datasheet (Raspberry Pi)