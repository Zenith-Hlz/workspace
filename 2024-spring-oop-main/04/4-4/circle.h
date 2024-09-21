#pragma once

#include <cmath>
#include "shape.h"

class Circle : public Shape2D
{
public:
    double radius;
    Circle(double r) : radius(r) {}
    double perimeter() const override
    {
        return 2 * PI * radius;
    }
    double area() const override
    {
        return PI * pow(radius, 2);
    }
    virtual ~Circle() {}
};