#include <stdio.h>
#include <stdint.h>
#include <alloca.h>

typedef struct __attribute__((packed))
{
    uint8_t signature[2];
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;

    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_m;
    uint32_t y_pixels_per_m;
    uint32_t colors_used;
    uint32_t important_colors;
} BMP;

typedef struct __attribute__((packed))
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t reserved;
} Bitfield;

int load_bmp_header(BMP *target, FILE *f)
{
    fread(target, sizeof(uint8_t), sizeof(BMP), f);

    int bitfield_offset = 16; // this depends on other values set, like BMP.compression

/*
    Bitfield *ct = (Bitfield *)alloca(bitfield_offset);
    fread(ct, sizeof(uint8_t), bitfield_offset, f);
*/
    fseek(f, bitfield_offset, SEEK_CUR);

    return 1;
}

int pixel_data_size(BMP *bmp)
{
    // bmp filesize reported from aseprite is incorrect
    // otherwise this would work
    // see issue: 
    // bmp.file_size - sizeof(BMP) - bitfield_offset;

    return bmp->width * bmp->height * bmp->bits_per_pixel / 8;
}

int load_bmp_pixel_data(uint8_t *target, BMP *bmp, FILE *f)
{
    fread(target, sizeof(uint8_t), pixel_data_size(bmp), f);

    return 1;
}