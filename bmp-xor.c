#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define BITMAP_INFO_HEADER_SIZE  40
#define BITMAP_INFO_HEADER_START 14

int32_t main(int32_t argc, int8_t *argv[])
{
    if (argc != 4) {
        printf("usage:\nxor %%s %%s %%s, input bitmap, one time pad key, output bitmap\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 2;
    }

    uint32_t header_size = 0;
    fseek(fin, BITMAP_INFO_HEADER_START, SEEK_SET);
    fread(&header_size, sizeof(uint32_t), 1, fin);

    if (header_size != BITMAP_INFO_HEADER_SIZE) {
        fprintf(
            stderr,
            "Information header size found: %u bytes\n"
            "Only 40 bytes header is supported\n",
            header_size
        );

        fclose(fin);
        return 3;
    }

    fclose(fin);
    return 0;
}
