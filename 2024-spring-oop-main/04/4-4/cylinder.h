#pragma once

#include <cmath>
#include "shape.h"

class Cylinder : public Shape3D
{
public:
    double baseRadius;
    double height;
    Cylinder(double r, double h) : baseRadius(r), height(h) {}
    double volume() const override
    {
        return PI * pow(baseRadius, 2) * height;
    }
    double area() const override
    {
        return 2 * PI * pow(baseRadius, 2) + 2 * PI * baseRadius * height;
    }
    virtual ~Cylinder() {}
};