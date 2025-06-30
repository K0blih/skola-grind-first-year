#include "Rectangle.h"

Rectangle::Rectangle(double a, double b) : a(a), b(b)
{
}

double Rectangle::getArea()
{
    return this->a * this->b;
}

double Rectangle::getCircumference()
{
    return 2 * (this->a + this->b);
}
