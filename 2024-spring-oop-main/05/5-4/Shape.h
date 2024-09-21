#include <iostream>
#include <string>

template <class RealShape>
class Shape {
protected:
    int a, b;

public:
    static int createdCount;
    static int aliveCount;

    Shape(int a, int b) : a(a), b(b) {
        createdCount++;
        aliveCount++;
    }

    ~Shape() {
        aliveCount--;
    }

    std::string type() {
        return static_cast<RealShape*>(this)->typeImpl();
    }

    int area() {
        return static_cast<RealShape*>(this)->areaImpl();
    }

    Shape* print() {
        std::cout << "Area of " << this->type() << ": " << this->area() << std::endl;
        return this;
    }

    Shape* zoom(int k) {
        a *= k;
        b *= k;
        return this;
    }

    static int getCreate() {
        return createdCount;
    }

    static int getAlive() {
        return aliveCount;
    }
};

template <class RealShape> int Shape<RealShape>::createdCount = 0;
template <class RealShape> int Shape<RealShape>::aliveCount = 0;

class Triangle : public Shape<Triangle> {
public:
    Triangle(int a, int b) : Shape<Triangle>(a, b) {}

    std::string typeImpl() {
        return "Triangle";
    }

    int areaImpl() {
        return (a * b) / 2;
    }
};

class Rectangle : public Shape<Rectangle> {
public:
    Rectangle(int a, int b) : Shape<Rectangle>(a, b) {}

    std::string typeImpl() {
        return "Rectangle";
    }

    int areaImpl() {
        return a * b;
    }
};
