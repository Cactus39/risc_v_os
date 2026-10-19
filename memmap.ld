MEMORY
{
    FLASH (rx)  : ORIGIN = 0x10000000, LENGTH = 4M
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 512K
}

ENTRY(_start)

SECTIONS
{
    .text : {
        KEEP(*(.embedded_block))
        *(.text*)
    } > FLASH

    __stack_top = ORIGIN(RAM) + LENGTH(RAM);
}