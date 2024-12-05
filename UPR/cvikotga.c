#include "cvikotga.h"
#include <string.h>
#include <stdio.h>

void save_tga(HEADER header, PIXEL* pixel, char* outputPath) {
    int width = 0;
    int height = 0;
    memcpy(header.width, &width, 2);
    memcpy(header.height, &height, 2);

    FILE* image = fopen(outputPath, "wb");

    fwrite(&header, sizeof(header), 1, image); 
    fwrite(pixel, sizeof(PIXEL), width * height, image);

    fclose(image);
}