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

class Line {
public:
    Point2D m_start;
    Point2D m_end;
    int m_color;
    int m_bgcolor;

    Line(Point2D start, Point2D end, int color, int bgcolor)
        : m_start(start), m_end(end), m_color(color), m_bgcolor(bgcolor) {}

    void draw() {
        int x1 = m_start.x;
        int y1 = m_start.y;
        int x2 = m_end.x;
        int y2 = m_end.y;
        int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
    
        while (true) {
            lcd_put_pixel(x1, y1, m_color);
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x1 += sx; }
            if (e2 <= dx) { err += dx; y1 += sy; }
        }
    }

    void hide() {
        int x1 = m_start.x;
        int y1 = m_start.y;
        int x2 = m_end.x;
        int y2 = m_end.y;
        int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
    
        while (true) {
            lcd_put_pixel(x1, y1, m_bgcolor);
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x1 += sx; }
            if (e2 <= dx) { err += dx; y1 += sy; }
        }
    }
};
    
class Circle {
public:
    Point2D m_center;
    int m_radius;
    int m_color;
    int m_bgcolor;

    Circle(Point2D center, int radius, int color, int bgcolor)
        : m_center(center), m_radius(radius), m_color(color), m_bgcolor(bgcolor) {}

    void draw() {
        int x0 = m_center.x;
        int y0 = m_center.y;
        int radius = m_radius;
        int x = radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (radius << 1);
    
        while (x >= y) {
            lcd_put_pixel(x0 + x, y0 + y, m_color);
            lcd_put_pixel(x0 + y, y0 + x, m_color);
            lcd_put_pixel(x0 - y, y0 + x, m_color);
            lcd_put_pixel(x0 - x, y0 + y, m_color);
            lcd_put_pixel(x0 - x, y0 - y, m_color);
            lcd_put_pixel(x0 - y, y0 - x, m_color);
            lcd_put_pixel(x0 + y, y0 - x, m_color);
            lcd_put_pixel(x0 + x, y0 - y, m_color);
    
            if (err <= 0) {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0) {
                x--;
                dx += 2;
                err += dx - (radius << 1);
            }
        }
    }

    void hide() {
        int x0 = m_center.x;
        int y0 = m_center.y;
        int radius = m_radius;
        int x = radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (radius << 1);
    
        while (x >= y) {
            lcd_put_pixel(x0 + x, y0 + y, m_bgcolor);
            lcd_put_pixel(x0 + y, y0 + x, m_bgcolor);
            lcd_put_pixel(x0 - y, y0 + x, m_bgcolor);
            lcd_put_pixel(x0 - x, y0 + y, m_bgcolor);
            lcd_put_pixel(x0 - x, y0 - y, m_bgcolor);
            lcd_put_pixel(x0 - y, y0 - x, m_bgcolor);
            lcd_put_pixel(x0 + y, y0 - x, m_bgcolor);
            lcd_put_pixel(x0 + x, y0 - y, m_bgcolor);
    
            if (err <= 0) {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0) {
                x--;
                dx += 2;
                err += dx - (radius << 1);
            }
        }
    }
};

// class Character : public GraphElement 
// {
// public:
//     // position of character
//     Point2D m_pos;
//     // character
//     char m_character;

//     Character( Point2D t_pos, char t_char, RGB t_fg, RGB t_bg ) : 
//       GraphElement( t_fg, t_bg ), m_pos( t_pos ), m_character( t_char ) {};

//     void draw() { }; // IMPLEMENT!!!
// };