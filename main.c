
int     counter = 5;
int     bss;
char    *str = "stringsss";

int     main(void) {
    for (;;) {
        counter++;
        __asm__ volatile ("ecall");
    }
}