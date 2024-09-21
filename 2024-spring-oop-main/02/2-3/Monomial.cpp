#include "Monomial.h"

#include <cmath>

Monomial::Monomial() {}

Monomial::Monomial(int _c, int _d)
{
    coe = _c;
    if (_c != 0)
        deg = _d;
    else
        deg = 0;
}

Monomial Monomial::operator+(const Monomial &x)
{
    Monomial newMono(coe + x.coe, deg);
    return newMono;
}

Monomial Monomial::operator-(const Monomial &x)
{
    Monomial newMono(coe - x.coe, deg);
    return newMono;
}

Monomial Monomial::operator*(const Monomial &x)
{
    Monomial newMono(coe * x.coe, deg + x.deg);
    return newMono;
}

Monomial Monomial::operator/(const Monomial &x)
{
    Monomial newMono(coe / x.coe, deg - x.deg);
    return newMono;
}

int Monomial::definite_integral(const int a, const int b)
{
    Monomial m(coe / (deg + 1), deg + 1);
    return m.get_val(b) - m.get_val(a);
}

Monomial Monomial::derive()
{
    Monomial newMono(coe * deg, deg - 1);
    return newMono;
}

int Monomial::get_val(int x)
{
    return coe * pow(x, deg);
}

std::istream &operator>>(std::istream &in, Monomial &m)
{
    std::string s;
    in >> s;
    std::string coe_str = s.substr(0, s.find("x"));
    std::string deg_str = s.substr(s.find("^") + 1);
    m.coe = std::stoi(coe_str);
    m.deg = std::stoi(deg_str);
    return in;
}

std::ostream &operator<<(std::ostream &out, const Monomial &m)
{
    out << m.coe << "x^" << m.deg << "\n";
    return out;
}