#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main (int argc, char* argv[]) {

    char* inputFIle = "0";
    char* outputFile = "0";
    char* fontFile = "0";
    char* alphabet[26];

    if (argc != 4) {
        printf("Wrong parameters\n");
        return 1;
    }
    else {
        inputFIle = argv[1];
        outputFile = argv[2];
        fontFile = argv[3];
    }

    return 0;
}