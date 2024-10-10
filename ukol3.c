#include <stdio.h>
#include "drawing.h"

void dashedLine(int length);
// min size 2
void stairs(int size, int count);
// min length is 4 and height is 5
void flower(int length, int height);
void meadow(int length, int height);
void animation();

int main() {
    // Keep this line here
    clear_screen();

    // Load the input - what should be drawn.
    int drawing = 0;
    scanf("%d", &drawing);  

    // Put your drawing code here
    switch (drawing) {
        case 0:
        set_white_color();
        move_to(10, 1);
        dashedLine(9);
        set_red_color();
        move_to(5, 20);
        dashedLine(10);
        set_green_color();
        move_to(8, 10);
        dashedLine(5);
        break;

        case 1:
        set_red_color();
        move_to(10, 20);
        stairs(3, 3);
        set_green_color();
        move_to(6, 50);
        stairs(5, 1);
        set_white_color();
        move_to(9, 1);
        stairs(4, 2);
        break;

        case 2:
        move_to(20, 10);
        flower(5, 7);
        move_to(16, 20);
        flower(4, 5);
        move_to(18, 30);
        flower(6, 8);
        break;

        case 3:
        meadow(60, 20);
        break;

        case 4:
        animation();
        break;
    }



    // Keep this line here
    end_drawing();

    return 0;
}

void dashedLine(int length) {
    for (int i = 0; i < length; i++) {
        draw_pixel();
        move_right();
        draw_pixel();
        move_right();
        move_right();
        move_right();
    }
}

void stairs(int size, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < size; j++) {
        draw_pixel();
        move_right();
        draw_pixel();
        move_left();
        move_up();
        }
        move_down();
        for (int j = 0; j < size * 2 + 1; j++) {
            draw_pixel();
            move_right();
        }
        move_left();
        move_left();
    }
}

void flower(int length, int height) {
    set_green_color();
    for (int i = 0; i < height - length; i++) {
        draw_pixel();
        move_up();
    }
    set_red_color();
    for (int i = 0; i < length-3; i++) {
        draw_pixel();
        move_left();
        move_up();
        draw_pixel();
    }
    for (int i = 0; i < length-3; i++) {
        draw_pixel();
        move_up();
        move_right();
        draw_pixel();
    }
    for (int i = 0; i < length-3; i++) {
        draw_pixel();
        move_right();
        move_down();
        draw_pixel();
    }
    for (int i = 0; i < length-3; i++) {
        draw_pixel();
        move_down();
        move_left();
        draw_pixel();
    }
}

void meadow(int length, int height) {
    move_to(height, length-50);
    flower(5, 7);
    move_to(height, length-40);
    flower(4, 5);
    move_to(height, length-30);
    flower(4, 6);
    move_to(height, length-20);
    flower(6, 7);
    move_to(height, length-10);
    flower(4, 6);
    move_to(height, length);
    flower(4, 6);

    move_to(height-4, length-45);
    flower(7, 9);
    move_to(height-4, length-35);
    flower(4, 5);
    move_to(height-4, length-25);
    flower(5, 8);
    move_to(height-4, length-15);
    flower(7, 8);
    move_to(height-4, length-5);
    flower(4, 6);
    move_to(height-4, length+5);
    flower(6, 8);
}

void animation() {
    int i = 4;
    int j = 6;
    int iVelocity = 1;
    int jVelocity = 1;
    while (1) {
        move_to(20, 20);
        flower(i, j);
        animate();
        clear_screen();
        if (i >= 8 || i <= 3) {
            iVelocity = -iVelocity;
        }
        if (j >= 10 || j <= 5) {
            jVelocity = -jVelocity;
        }
        i += iVelocity;
        j += jVelocity;
    }
}