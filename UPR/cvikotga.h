// #pragma once
#ifndef _CVIKOTGA_H_
#define _CVIKOTGA_H_

typedef struct {
    char idlength;
    char colourmaptype;
    char datatypecode;
    char colourmaporigin[2];
    char colourmaplength[2];
    char colourmapdepth;
    char x_origin[2];
    char y_origin[2];
    char width[2];
    char height[2];
    char bitsperpixel;
    char imagedescriptor;
} HEADER;

typedef struct {
    char B;
    char G;
    char R;
} PIXEL;

void save_tga(HEADER header, PIXEL* pixel, char* outputPath);

#endif