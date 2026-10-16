#include <stdio.h>
#include "head.h"

int main(void) {
    printf("Hello, World!\nx = %d y = %d\n", x, y);
    printf("%d\n", ok);
    for (int i = 0; i < 2; i++)
    {
        printf("block %d\n", i);
    }

    return 0;
}
