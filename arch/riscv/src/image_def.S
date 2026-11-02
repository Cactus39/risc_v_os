.section .MBR, "a"

.balign 4
MBR_start:
/* PICOBIN_BLOCK_MARKER_START   */
    .word 0xffffded3

/* IMAGE DEF ITEM               */
    .byte 0x42, 0x01                // TYPE = IMAGE DEF | SIZE 1W
    .hword 0x1101                   // EXE RP2350 | EXE_CPU_RISCV | SECURITY | IMAGE_TYPE EXE

/* ENTTY POINT ITEM             */
    .byte 0x44, 0x03                // TYPE = ENTRY POINT | SIZE 3W
    .hword 0
    .word _start                    // INITIAL PC
    .word __stack_top               // INITIAL SP

/* LAST ITEM                    */
    .byte 0xff                              // TYPE = LAST
    .hword (MBR_end - MBR_start - 16) / 4   // SIZE W OF ALL PREVIOUS ITEMS
    .byte 0

/* LINK TO NEXT BLOCK           */
    .word 0                         // LINK TO SELF

/* PICOBIN_BLOCK_MARKER_END     */
    .word 0xab123579
MBR_end:

/* datasheet rp2350 5.1.5 */
/* datasheet rp2350 5.9.1 */
