#pragma once

#include <cmath>
#include "shape.h"

class Cone : public Shape3D
{
public:
    double baseRadius;
    double height;
    Cone(double r, double h) : baseRadius(r), height(h) {}
    double volume() const override
    {
        return PI * pow(baseRadius, 2) * height / 3;
    }
    double area() const override
    {
        return PI * pow(baseRadius, 2) + PI * baseRadius * sqrt(pow(baseRadius,2)+pow(height,2));
    }
    virtual ~Cone() {}
};