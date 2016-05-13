#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define BITMAP_INFO_HEADER_SIZE  40
#define BITMAP_INFO_HEADER_START 14

typedef struct {
    uint16_t type;
    uint32_t size;
    uint32_t reserved;
    uint32_t offset_bits;
} bitmap_file_header_t;

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

    bitmap_file_header_t file_header;
    memset(&file_header, 0, sizeof(bitmap_file_header_t));

    fseek(fin, 0, SEEK_SET);
    fread(&file_header.type,        sizeof(uint16_t), 1, fin);
    fread(&file_header.size,        sizeof(uint32_t), 1, fin);
    fread(&file_header.reserved,    sizeof(uint32_t), 1, fin);
    fread(&file_header.offset_bits, sizeof(uint32_t), 1, fin);

    fclose(fin);
    return 0;
}
