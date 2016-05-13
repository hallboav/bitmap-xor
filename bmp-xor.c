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

// v3
typedef struct {
    uint32_t size;
    int32_t  px_width;
    int32_t  px_height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;  // in bytes
    int32_t  x_pixels_per_meter;
    int32_t  y_pixels_per_meter;
    uint32_t colors_used; // 2 ^ bit_count
    uint32_t color_important;
} bitmap_info_header_t;

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
} color_definition_t;

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
    bitmap_info_header_t info_header;
    memset(&file_header, 0, sizeof(bitmap_file_header_t));
    memset(&info_header, 0, sizeof(bitmap_info_header_t));

    fseek(fin, 0, SEEK_SET);
    fread(&file_header.type,        sizeof(uint16_t), 1, fin);
    fread(&file_header.size,        sizeof(uint32_t), 1, fin);
    fread(&file_header.reserved,    sizeof(uint32_t), 1, fin);
    fread(&file_header.offset_bits, sizeof(uint32_t), 1, fin);

    // É suportado chamar apenas um fread, pois
    // sizeof(bitmap_info_header_t) é multiplo de 8 (sem padding)
    fread(&info_header, 1, sizeof(bitmap_info_header_t), fin);

    if (info_header.bit_count != 1) {
        fprintf(
            stderr,
            "Bit depth found: %u bits\n"
            "Only 1 bit depth is supported\n",
            info_header.bit_count
        );

        fclose(fin);
        return 4;
    }

    // Lendo tabela de cores
    color_definition_t indexed_color[info_header.colors_used];
    memset(indexed_color, 0, info_header.colors_used * sizeof(color_definition_t));
    fread(indexed_color, sizeof(color_definition_t), info_header.colors_used, fin);

    fclose(fin);
    return 0;
}
