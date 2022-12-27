# parse-bmp-in-c
not complete, only tested on macos with aseprite bmps

# example usage

```c
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main()
{
    BMP bmp;

    FILE *f = fopen("sprite.bmp", "r");
    load_bmp_header(&bmp, f);
    uint8_t *pixel_data = (uint8_t *)malloc(pixel_data_size(&bmp));
    load_bmp_pixel_data(pixel_data, &bmp, f);
    fclose(f);

    printf("signature: %c%c\n", bmp.signature[0], bmp.signature[1]);
    printf("file_size: %d\n", bmp.file_size);
    printf("reserved: %d\n", bmp.reserved);
    printf("data_offset: %d\n", bmp.data_offset);
    printf("size: %d\n", bmp.size);
    printf("width: %d\n", bmp.width);
    printf("height: %d\n", bmp.height);

    printf("planes: %d\n", bmp.planes);
    printf("bits_per_pixel: %d\n", bmp.bits_per_pixel);
    printf("compression: %d\n", bmp.compression);
    printf("image_size: %d\n", bmp.image_size);
    printf("x_pixels_per_m: %d\n", bmp.x_pixels_per_m);
    printf("y_pixels_per_m: %d\n", bmp.y_pixels_per_m);
    printf("colors_used: %d\n", bmp.colors_used);
    printf("important_colors: %d\n", bmp.important_colors);

    for (int i = 0; i < pixel_data_size(&bmp); i += 4) {
        printf("rgba: %d %d %d %d\n", pixel_data[i], pixel_data[i + 1], pixel_data[i + 2], pixel_data[i + 3]);
    }

    free(pixel_data);

    return 0;
}
```
