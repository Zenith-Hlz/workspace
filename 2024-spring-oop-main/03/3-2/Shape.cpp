#include "Shape.h"

Shape::Shape(double w, double h) : width(w), height(h) {}
Shape::Shape(double r) : radius(r) {}
Shape::~Shape() {}

Rectangle::Rectangle(double w, double h) : Shape(w, h) {}
double Rectangle::getArea() const
{
    return width * height;
}

Circle::Circle(double r) : Shape(r) {}
double Circle::getArea() const
{
    return 3.14 * radius * radius;
}
