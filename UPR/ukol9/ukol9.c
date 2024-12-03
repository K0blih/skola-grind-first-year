#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef unsigned char byte;

typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

Pixel* load_pixels(TGAHeader header, FILE* file);

int main (int argc, char* argv[]) {

    char* inputFile = "0";
    char* outputFile = "0";
    char* fontFile = "0";
    char alphabet[26][20];
    Pixel* letterPixels[26] = {NULL};
    int letterWidth[26] = {0};
    int letterHeight[26] = {0};
    int n = sizeof(alphabet) / sizeof(alphabet[0]);

    // arg check
    if (argc != 4) {
        printf("Wrong parameters\n");
        return 1;
    }
    else {
        inputFile = argv[1];
        outputFile = argv[2];
        fontFile = argv[3];
    }

    // input file load
    FILE* file = NULL;
    file = fopen(inputFile, "rb");
    if (file == NULL) {
        printf("Could not load image\n");
        return 1;
    }

    TGAHeader headerInput = {0};
    fread(&headerInput, sizeof(TGAHeader), 1, file);
    Pixel* inputPixels = load_pixels(headerInput, file);

    fclose(file);

    // font letters load
    for (int i = 0; i < n; i++) {
        char currentChar = (char)('A' + i);
        sprintf(alphabet[i], "%s/%c.tga", fontFile, currentChar);

        FILE* letter = NULL;
        letter = fopen(alphabet[i], "rb");
        if (letter == NULL) {
            return 1;
        }
        
        TGAHeader headerLetter = {0};
        fread(&headerLetter, sizeof(TGAHeader), 1, letter);
        memcpy(&letterWidth[i], headerLetter.width, 2);
        memcpy(&letterHeight[i], headerLetter.height, 2);
        letterPixels[i] = load_pixels(headerLetter, letter);
        
        fclose(letter);
    }

    // get top bottom and strings
    int top = 0;
    int bottom = 0;
    char tbBuffer[10];

    fgets(tbBuffer, sizeof(tbBuffer), stdin);

    char* token = strtok(tbBuffer, " ");
    if (token != NULL) {
        top = atoi(token);
    }
    token = strtok(NULL, " ");
    if (token != NULL) {
        bottom = atoi(token);
    }

    char lnBuffer[101];
    for (int i = 0; i < (top + bottom); i++) {
        fgets(lnBuffer, sizeof(lnBuffer), stdin);
        for(int j = 0; lnBuffer[j] != '\0'; j++) {
            lnBuffer[j] = (char)toupper(lnBuffer[j]);
        }
    }

    // remake the image

    

    // create output file
    FILE* output = NULL;
    output = fopen(outputFile, "wb");
    int width = 0;
    int height = 0;
    memcpy(&width, headerInput.width, 2);
    memcpy(&height, headerInput.height, 2);

    // printf("%d\n", letterWidth[0]);
    // printf("%d\n", letterHeight[0]);
    // for (int row = 0; row < height; row++) {
    //     for (int col = 0; col < width; col++) {
    //         Pixel* pixel = inputPixels + (row * width + col);
    //         pixel->red = 0;
    //         pixel->green = 0;
    //         pixel->blue = 0;
    //     }
    // }
    for (int row = 0; row < letterHeight[0]; row++) {
        for (int col = 0; col < letterWidth[0]; col++) {
            Pixel* inputPixel = inputPixels + ((row + 100)  * width + col + width / 2 - letterWidth[0] / 2);
            Pixel* pixel = letterPixels[0] + (row * letterWidth[0] + col);
            if (pixel->red == 255 && pixel->green == 255 && pixel->blue == 255) {
                inputPixel->red = pixel->red;
                inputPixel->green = pixel->green;
                inputPixel->blue = pixel->blue;
            }
        }
    }

    fwrite(&headerInput, sizeof(TGAHeader), 1, output);
    fwrite(inputPixels, sizeof(Pixel) * width * height, 1, output);
    fclose(output);

    // free memory
    free(inputPixels);
    inputPixels = NULL;
    for (int i = 0; i < n; i++) {
        if (letterPixels[i] != NULL) {
            free(letterPixels[i]);
            letterPixels[i] = NULL;
        }
    }

    return 0;
}

Pixel* load_pixels(TGAHeader header, FILE* file) {
    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    Pixel* pixels = (Pixel*)malloc(sizeof(Pixel) * width * height);
    assert(fread(pixels, sizeof(Pixel) * width * height, 1, file) == 1);
    return pixels;
}