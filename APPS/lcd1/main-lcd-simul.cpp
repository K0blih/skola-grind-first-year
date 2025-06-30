// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 09/2019
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         OpenCV simulator of LCD
//
// **************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lcd_lib.h"
#include "font8x8.h"
#include "fonts/font16x26_msb.h"
#include "graph_class.hpp"

void drawCircle(Point2D center, int32_t radius, uint16_t fg_color);
void drawLine(Point2D p1, Point2D p2, uint16_t fg_color);
void drawCharacter(Point2D pos, char character, uint16_t fg_color, uint16_t bg_color, bool bigFont);

// struct cts_points_t {
//     uint16_t m_num_points;          // Number of detected points
//     struct {
//         uint16_t x;                 // x-point coordinate
//         uint16_t y;                 // y-point coordinate
//         uint16_t size;              // size of touch
//     } m_points[5];                  // array of up to five points
// };

// Touch screen controller functions (declarations)
// int32_t cts_init();
// int32_t cts_get_ts_points(cts_points_t *t_points);

// uint16_t g_selected_color = 0xFFFF; // Default color is white
// bool g_prev_touch_active = false;   // Was touch active in previous frame - properly initialized here

int main()
{
    lcd_init();                     // LCD initialization

    uint16_t l_color_red = 0xF800;
    uint16_t l_color_green = 0x07E0;
    uint16_t l_color_blue = 0x001F;
    uint16_t l_color_white = 0xFFFF;
    uint16_t l_color_black = 0x0000;
    // RGB red = { 255, 0, 0 };
    // RGB green = { 0, 255, 0 };
    // RGB blue = { 0, 0, 255 };
    // RGB white = { 255, 255, 255 };
    // RGB black = { 0, 0, 0 };
    // int width = LCD_WIDTH;
    // int height = LCD_HEIGHT;

    // clear display
    // for (int y = 0; y < LCD_HEIGHT; y++) {
    //     for (int x = 0; x < LCD_WIDTH; x++) {
    //         lcd_put_pixel(x, y, l_color_black);
    //     }
    // }

    // simple animation display four color square using LCD_put_pixel function
    // int l_limit = LCD_HEIGHT - 40;
    // for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
    // {
    //     for ( int i = 0; i < l_limit; i++ )
    //     {
    //         lcd_put_pixel( ofs + i, ofs + 0, l_color_red );
    //         lcd_put_pixel( ofs + 0, ofs + i, l_color_green );
    //         lcd_put_pixel( ofs + i, ofs + l_limit, l_color_blue );
    //         lcd_put_pixel( ofs + l_limit, ofs + i, l_color_white );
    //     }
    // }

    // Circle
    // Point2D circle_center = { 100, 100 };
    // int radius = 40;
    // drawCircle(circle_center, radius, l_color_white);

    // // Character
    // Point2D char_pos = { 200, 200 };
    // char letter = 'A';  // Character to display
    // drawCharacter(char_pos, letter, l_color_white, l_color_black, 1);

    // // Rectangle
    // Point2D top_left = {50, 50};
    // Point2D top_right = {200, 50};
    // Point2D bottom_left = {50, 150};
    // Point2D bottom_right = {200, 150};

    // // Create the four lines for the rectangle
    // // Top line
    // drawLine(top_left, top_right, l_color_red);

    // // Bottom line
    // drawLine(top_right, bottom_right, l_color_green);

    // // Left line
    // drawLine(bottom_right, bottom_left, l_color_blue);

    // // Right line
    // drawLine(bottom_left, top_left, l_color_white);

    Point2D circle_center = { LCD_WIDTH / 2, LCD_HEIGHT / 2 };
    int radius = 80;
    drawCircle(circle_center, radius, l_color_white);

    int rect_width = 200;
    int rect_height = 150;
    Point2D top_left = {(LCD_WIDTH - rect_width) / 2, (LCD_HEIGHT - rect_height) / 2};
    Point2D top_right = {(LCD_WIDTH + rect_width) / 2, (LCD_HEIGHT - rect_height) / 2};
    Point2D bottom_left = {top_left.x, top_left.y + rect_height};
    Point2D bottom_right = {top_left.x + rect_width, top_left.y + rect_height};

    // Create the four lines for the rectangle
    drawLine(top_left, top_right, l_color_red);
    drawLine(top_right, bottom_right, l_color_green);
    drawLine(bottom_right, bottom_left, l_color_blue);
    drawLine(bottom_left, top_left, l_color_white);

    Point2D pos_r = { 10, 10 };
    drawCharacter(pos_r, 'R', l_color_red, l_color_black, true);
    
    Point2D pos_g = { LCD_WIDTH - 26, 10 };
    drawCharacter(pos_g, 'G', l_color_green, l_color_black, true);
    
    Point2D pos_b = { 10, LCD_HEIGHT - 36 };
    drawCharacter(pos_b, 'B', l_color_blue, l_color_black, true);
    
    Point2D pos_w = { LCD_WIDTH - 26, LCD_HEIGHT - 36 };
    drawCharacter(pos_w, 'W', l_color_white, l_color_black, true);

    cv::imshow( LCD_NAME, g_canvas );   // refresh content of "LCD"
    cv::waitKey( 0 );                   // wait for key 
}

void drawCircle(Point2D center, int32_t radius, uint16_t fg_color)
{
    int center_x = center.x;
    int center_y = center.y;
    int x = 0;
    int y = radius;
    int decision = 3 - 2 * radius;

    while (y >= x) {
        lcd_put_pixel(center_x + x, center_y + y, fg_color);
        lcd_put_pixel(center_x - x, center_y + y, fg_color);
        lcd_put_pixel(center_x + x, center_y - y, fg_color);
        lcd_put_pixel(center_x - x, center_y - y, fg_color);
        lcd_put_pixel(center_x + y, center_y + x, fg_color);
        lcd_put_pixel(center_x - y, center_y + x, fg_color);
        lcd_put_pixel(center_x + y, center_y - x, fg_color);
        lcd_put_pixel(center_x - y, center_y - x, fg_color);

        x++;

        if (decision > 0) {
            y--;
            decision = decision + 4 * (x - y) + 10;
        } else {
            decision = decision + 4 * x + 6;
        }
    }
}

void drawLine(Point2D p1, Point2D p2, uint16_t fg_color)
{
    int x_start = p1.x;
    int y_start = p1.y;
    int x_end = p2.x;
    int y_end = p2.y;

    int delta_x = abs(x_end - x_start);
    int delta_y = abs(y_end - y_start);

    int step_x;
    int step_y;

    if (x_end > x_start) {
        step_x = 1;
    } else {
        step_x = -1;
    }

    if (y_end > y_start) {
        step_y = 1;
    } else {
        step_y = -1;
    }

    int error = delta_x - delta_y;

    int current_x = x_start;
    int current_y = y_start;

    while (true) {
        lcd_put_pixel(current_x, current_y, fg_color);

        if (current_x == x_end && current_y == y_end) {
            break;
        }

        int error2 = 2 * error;

        if (error2 > -delta_y) {
            error -= delta_y;
            current_x += step_x;
        }

        if (error2 < delta_x) {
            error += delta_x;
            current_y += step_y;
        }
    }
}

void drawCharacter(Point2D pos, char character, uint16_t fg_color, uint16_t bg_color, bool bigFont)
{
    if (bigFont) {
        for (int y = 0; y < 26; y++) {
            uint16_t row_data = font[(int)character][y];

            for (int x = 0; x < 16; x++) {
                if (row_data & (1 << (15 - x))) {  // Check if the x-th bit is set
                    lcd_put_pixel(pos.x + x, pos.y + y, fg_color);  // Draw the foreground color
                } else {
                    lcd_put_pixel(pos.x + x, pos.y + y, bg_color);  // Draw the background color
                }
            }
        }
    } else {
        for (int y = 0; y < 8; y++) {
            uint8_t mask = 1;
            for (int x = 0; x < 8; x++) {
                if (font8x8[(int)character][y] & mask) {
                    lcd_put_pixel(pos.x + x, pos.y + y, fg_color);
                } else {
                    lcd_put_pixel(pos.x + x, pos.y + y, bg_color);
                }
                mask = mask << 1;
            }
        }
    }
}

// void handleTouchInput()
// {
//     cts_points_t touch_points;
//     int32_t touch_result = cts_get_ts_points(&touch_points);
    
//     // Define colors
//     uint16_t l_color_red = 0xF800;
//     uint16_t l_color_green = 0x07E0;
//     uint16_t l_color_blue = 0x001F;
//     uint16_t l_color_white = 0xFFFF;
    
//     // Check if touch is active
//     if (touch_result > 0) {
//         // Touch is active, process the points
//         for (int i = 0; i < touch_points.m_num_points; i++) {
//             int x = touch_points.m_points[i].x;
//             int y = touch_points.m_points[i].y;
//             int size = touch_points.m_points[i].size;
            
//             // Constrain coordinates to display dimensions
//             if (x >= LCD_WIDTH) x = LCD_WIDTH - 1;
//             if (y >= LCD_HEIGHT) y = LCD_HEIGHT - 1;
            
//             // Define the corner regions for color selection
//             const int corner_size = 40;
            
//             // Top-left (Red)
//             if (x < corner_size && y < corner_size) {
//                 if (!g_prev_touch_active) {  // Only trigger on new touch
//                     g_selected_color = l_color_red;
//                     printf("Red color selected\n");
                    
//                     // Highlight the selected letter with a frame
//                     Point2D top_left = { 5, 5 };
//                     Point2D bottom_right = { 30, 40 };
//                     // drawRectangle(top_left, bottom_right, l_color_red);
//                 }
//             }
//             // Top-right (Green)
//             else if (x > LCD_WIDTH - corner_size && y < corner_size) {
//                 if (!g_prev_touch_active) {  // Only trigger on new touch
//                     g_selected_color = l_color_green;
//                     printf("Green color selected\n");
                    
//                     // Highlight the selected letter with a frame
//                     Point2D top_left = { LCD_WIDTH - 30, 5 };
//                     Point2D bottom_right = { LCD_WIDTH - 5, 40 };
//                     // drawRectangle(top_left, bottom_right, l_color_green);
//                 }
//             }
//             // Bottom-left (Blue)
//             else if (x < corner_size && y > LCD_HEIGHT - corner_size) {
//                 if (!g_prev_touch_active) {  // Only trigger on new touch
//                     g_selected_color = l_color_blue;
//                     printf("Blue color selected\n");
                    
//                     // Highlight the selected letter with a frame
//                     Point2D top_left = { 5, LCD_HEIGHT - 40 };
//                     Point2D bottom_right = { 30, LCD_HEIGHT - 5 };
//                     // drawRectangle(top_left, bottom_right, l_color_blue);
//                 }
//             }
//             // Bottom-right (White)
//             else if (x > LCD_WIDTH - corner_size && y > LCD_HEIGHT - corner_size) {
//                 if (!g_prev_touch_active) {  // Only trigger on new touch
//                     g_selected_color = l_color_white;
//                     printf("White color selected\n");
                    
//                     // Highlight the selected letter with a frame
//                     Point2D top_left = { LCD_WIDTH - 30, LCD_HEIGHT - 40 };
//                     Point2D bottom_right = { LCD_WIDTH - 5, LCD_HEIGHT - 5 };
//                     // drawRectangle(top_left, bottom_right, l_color_white);
//                 }
//             }
//             // Draw point at touched position if not in the corner regions
//             else {
//                 // Use the touch size to determine the radius of the drawing point
//                 // Normalize size (assuming size ranges from 0-100, adjust if different)
//                 int radius = (size > 0) ? (size / 10) + 1 : 2;
//                 if (radius > 10) radius = 10;  // Cap the maximum radius
                
//                 // Draw a filled circle at the touch point
//                 for (int dy = -radius; dy <= radius; dy++) {
//                     for (int dx = -radius; dx <= radius; dx++) {
//                         // Only draw pixels that are within the circle
//                         if (dx*dx + dy*dy <= radius*radius) {
//                             int draw_x = x + dx;
//                             int draw_y = y + dy;
                            
//                             // Make sure we're within the display boundaries
//                             if (draw_x >= 0 && draw_x < LCD_WIDTH && 
//                                 draw_y >= 0 && draw_y < LCD_HEIGHT) {
//                                 lcd_put_pixel(draw_x, draw_y, g_selected_color);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         g_prev_touch_active = true;
//     }
//     else if (touch_result == 0) {
//         // Touch was released
//         g_prev_touch_active = false;
//     }
//     // If touch_result is -1, touch screen is not active, do nothing
// }