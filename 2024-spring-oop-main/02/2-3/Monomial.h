#pragma once

#include <iostream>
#include <string>
#include <cmath>

class Monomial
{
private:
    int coe;
    int deg;

public:
    Monomial();
    Monomial(int _c, int _d);
    Monomial operator+(const Monomial &x);
    Monomial operator-(const Monomial &x);
    Monomial operator*(const Monomial &x);
    Monomial operator/(const Monomial &x);
    int definite_integral(const int a, const int b);
    Monomial derive();
    int get_val(int x);
    // TODO
    friend std::istream &operator>>(std::istream &in, Monomial &m);
    friend std::ostream &operator<<(std::ostream &out, const Monomial &m);
};
