#include "Circle.h"

Circle::Circle(double r) : r(r)
{
}

double Circle::getArea()
{
    return 3.14 * this->r * this->r;
}

double Circle::getCircumference()
{
    return 2 * 3.14 * this->r;
}
