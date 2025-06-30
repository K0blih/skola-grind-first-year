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

#include "lcd_lib.h"

// Simple graphic interface

struct Point2D 
{
    int32_t x, y;
};


struct RGB
{
    uint8_t r, g, b;
};


class GraphElement
{
public:
    // foreground and background color
    RGB m_fg_color, m_bg_color;

    // constructor
    GraphElement( RGB t_fg_color, RGB t_bg_color ) : 
        m_fg_color( t_fg_color ), m_bg_color( t_bg_color ) {}

    // ONLY ONE INTERFACE WITH LCD HARDWARE!!!
    void drawPixel( int32_t t_x, int32_t t_y ) { lcd_put_pixel( t_x, t_y, convert_RGB888_to_RGB565( m_fg_color ) ); }
    
    // Draw graphics element
    virtual void draw() = 0;
    
    // Hide graphics element
    virtual void hide() { swap_fg_bg_color(); draw(); swap_fg_bg_color(); }
private:
    // swap foreground and backgroud colors
    void swap_fg_bg_color() { RGB l_tmp = m_fg_color; m_fg_color = m_bg_color; m_bg_color = l_tmp; } 

    // IMPLEMENT!!! DONE
    // conversion of 24-bit RGB color into 16-bit color format
    uint16_t convert_RGB888_to_RGB565( RGB t_color ) 
    { 
        uint16_t r = (t_color.r >> 3) & 0x1F;   // 5 bits
        uint16_t g = (t_color.g >> 2) & 0x3F;   // 6 bits
        uint16_t b = (t_color.b >> 3) & 0x1F;   // 5 bits

        return (r << 11) | (g << 5) | b;
    }
};


class Pixel : public GraphElement
{
public:
    // constructor
    Pixel( Point2D t_pos, RGB t_fg_color, RGB t_bg_color ) : GraphElement( t_fg_color, t_bg_color ), m_pos( t_pos ) {}
    // Draw method implementation
    virtual void draw() { drawPixel( m_pos.x, m_pos.y ); }
    // Position of Pixel
    Point2D m_pos;
};


class Circle : public GraphElement
{
public:
    // Center of circle
    Point2D m_center;
    // Radius of circle
    int32_t m_radius;

    Circle( Point2D t_center, int32_t t_radius, RGB t_fg, RGB t_bg ) : 
        GraphElement( t_fg, t_bg ), m_center( t_center ), m_radius( t_radius ) {}

    // IMPLEMENT!!! DONE
    void draw()  {
        int center_x = m_center.x;
        int center_y = m_center.y;
        int radius = m_radius;
    
        int x = 0;
        int y = radius;
        int decision = 3 - 2 * radius;
    
        while (y >= x) {
            // 8-way symmetry
            lcd_put_pixel(center_x + x, center_y + y, 0xFFFF);
            lcd_put_pixel(center_x - x, center_y + y, 0xFFFF);
            lcd_put_pixel(center_x + x, center_y - y, 0xFFFF);
            lcd_put_pixel(center_x - x, center_y - y, 0xFFFF);
            lcd_put_pixel(center_x + y, center_y + x, 0xFFFF);
            lcd_put_pixel(center_x - y, center_y + x, 0xFFFF);
            lcd_put_pixel(center_x + y, center_y - x, 0xFFFF);
            lcd_put_pixel(center_x - y, center_y - x, 0xFFFF);
    
            x++;
    
            if (decision > 0) {
                y--;
                decision = decision + 4 * (x - y) + 10;
            } else {
                decision = decision + 4 * x + 6;
            }
        }
    }
};


class Character : public GraphElement 
{
public:
    // position of character
    Point2D m_pos;
    // character
    char m_character;

    Character( Point2D t_pos, char t_char, RGB t_fg, RGB t_bg ) : 
        GraphElement( t_fg, t_bg ), m_pos( t_pos ), m_character( t_char ) {};

    // IMPLEMENT!!! DONE
    void draw() 
    {
        char letter = m_character;

        for(int y = 0; y < 8; y++) {
            uint8_t mask = 1;

            for(int x = 0; x < 8; x++){
                if(font8x8[(int)letter][y] & mask) {
                    lcd_put_pixel(m_pos.x + x, m_pos.y + y, 0xFFFF);
                } 
                else {
                    lcd_put_pixel(m_pos.x + x, m_pos.y + y, 0x0000 );
                }

                mask = mask << 1;
            }
        }
    }
};


class Line : public GraphElement
{
public:
    // the first and the last point of line
    Point2D m_pos1, m_pos2;

    Line( Point2D t_pos1, Point2D t_pos2, RGB t_fg, RGB t_bg ) : 
        GraphElement( t_fg, t_bg ), m_pos1( t_pos1 ), m_pos2( t_pos2 ) {}

    // IMPLEMENT!!! DONE
    void draw() {
        int x_start = m_pos1.x;
        int y_start = m_pos1.y;
        int x_end   = m_pos2.x;
        int y_end   = m_pos2.y;
    
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
            lcd_put_pixel(current_x, current_y, 0xFFFF);  // white
    
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
};


