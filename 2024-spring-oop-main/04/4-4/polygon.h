#pragma once

#include <cmath>
#include "shape.h"

class Polygon : public Shape2D
{
public:
    double numSides;
    double sideLength;
    Polygon(double n, double s) : numSides(n), sideLength(s) {}
    double perimeter() const override
    {
        return numSides*sideLength;
    }
    double area() const override
    {
        return numSides * pow(sideLength, 2) / 4 / tan(PI / numSides);
    }
    virtual ~Polygon() {}
};