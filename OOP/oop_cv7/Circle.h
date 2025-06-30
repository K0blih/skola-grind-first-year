#pragma once
#include "Shape.h"
class Circle: public Shape
{
public:
	Circle(double r);
	double getArea() override;
	double getCircumference() override;

private:
	double r;

};

