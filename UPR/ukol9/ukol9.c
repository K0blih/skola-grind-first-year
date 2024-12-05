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
void modifyImage(Pixel* image, Pixel* letter, int letterHeight, int letterWidth, int imageWidth, int offsetY, int offsetX, int constOffset);

int main (int argc, char* argv[]) {

    char* inputFile = "0";
    char* outputFile = "0";
    char* fontFile = "0";
    char alphabet[26][20];
    Pixel* letterPixels[26] = {NULL};
    int letterWidth[26] = {0};
    int letterHeight[26] = {0};
    int width = 0;
    int height = 0;
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
    memcpy(&width, headerInput.width, 2);
    memcpy(&height, headerInput.height, 2);
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

    // get top, bottom, strings and modify the image
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

    int topOffsetY = 10;
    int topOffsetX = 0;
    for (int i = 0; i < top; i++) {

        fgets(lnBuffer, sizeof(lnBuffer), stdin);
        int letterCount = (int)strlen(lnBuffer) - 1;
        int constOffset = letterWidth[0] * letterCount / 2 + 10;

        for (int j = 0; lnBuffer[j] != '\0' && lnBuffer[j] != '\n'; j++) {
            lnBuffer[j] = (char)toupper((unsigned char)lnBuffer[j]);
            int index = lnBuffer[j] - 'A';
            topOffsetX = letterWidth[0] * letterCount;
            letterCount--;
            if (index >= 0 && index <= 25) {
                modifyImage(inputPixels, letterPixels[index], letterHeight[index], letterWidth[index], width, topOffsetY, topOffsetX, constOffset);
            }
        }
        topOffsetY += letterHeight[0] + 5;
    }

    int bottomOffsetY = height - letterHeight[0] * bottom - 10;
    int bottomOffsetX = 0;
    for (int i = 0; i < bottom; i++) {

        fgets(lnBuffer, sizeof(lnBuffer), stdin);
        int letterCount = (int)strlen(lnBuffer) - 1;
        int constOffset = letterWidth[0] * letterCount / 2 + 10;
        
        for (int j = 0; lnBuffer[j] != '\0' && lnBuffer[j] != '\n'; j++) {
            lnBuffer[j] = (char)toupper((unsigned char)lnBuffer[j]);
            int index = lnBuffer[j] - 'A';
            bottomOffsetX = letterWidth[0] * letterCount;
            letterCount--;
            if (index >= 0 && index <= 25) {
                modifyImage(inputPixels, letterPixels[index], letterHeight[index], letterWidth[index], width, bottomOffsetY, bottomOffsetX, constOffset);
            }
        }
        bottomOffsetY += letterHeight[0] + 5;
    }

    // create output file
    FILE* output = NULL;
    output = fopen(outputFile, "wb");

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

void modifyImage(Pixel* image, Pixel* letter, int letterHeight, int letterWidth, int imageWidth, int offsetY, int offsetX, int constOffset) {
    for (int row = 0; row < letterHeight; row++) {
        for (int col = 0; col < letterWidth; col++) {
            Pixel* inputPixel = image + ((row + offsetY)  * imageWidth + col + imageWidth / 2 - letterWidth / 2 - offsetX + constOffset);
            Pixel* pixel = letter + (row * letterWidth + col);
            if (pixel->red == 255 && pixel->green == 255 && pixel->blue == 255) {
                inputPixel->red = pixel->red;
                inputPixel->green = pixel->green;
                inputPixel->blue = pixel->blue;
            }
        }
    }
}