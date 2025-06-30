#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(double a, double b);
	double getArea() override;
	double getCircumference() override;

private:
	double a, b;
};

