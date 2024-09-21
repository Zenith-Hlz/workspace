#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
protected:
    double width, height, radius;

public:
    Shape(double w, double h);
    Shape(double r);
    virtual double getArea() const = 0;
    virtual ~Shape();
};

class Rectangle : public Shape
{
public:
    Rectangle(double w, double h);
    double getArea() const override;
};

class Circle : public Shape
{
public:
    Circle(double r);
    double getArea() const override;
};

#endif
