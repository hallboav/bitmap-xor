#include <stdio.h>
#include <stdint.h>

int32_t main(int32_t argc, int8_t *argv[])
{
    if (argc != 4) {
        printf("usage:\nxor %%s %%s %%s, input bitmap, one time pad key, output bitmap\n");
        return 1;
    }

    return 0;
}
