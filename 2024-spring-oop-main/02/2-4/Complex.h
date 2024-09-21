#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>

class Complex
{
private:
    double Re;
    double Im;

public:
    Complex(double real = 0.0, double imag = 0.0) : Re(real), Im(imag) {}

    Complex operator+(const Complex &other) const
    {
        return Complex(Re + other.Re, Im + other.Im);
    }

    Complex operator-(const Complex &other) const
    {
        return Complex(Re - other.Re, Im - other.Im);
    }

    Complex operator*(const Complex &other) const
    {
        double new_Re = Re * other.Re - Im * other.Im;
        double new_Im = Re * other.Im + Im * other.Re;
        return Complex(new_Re, new_Im);
    }

    Complex operator/(const Complex &other) const
    {
        double denominator = other.Re * other.Re + other.Im * other.Im;
        double new_Re = (Re * other.Re + Im * other.Im) / denominator;
        double new_Im = (Im * other.Re - Re * other.Im) / denominator;
        return Complex(new_Re, new_Im);
    }

    Complex operator~() const
    {
        return Complex(Re, -Im);
    }

    Complex operator-() const
    {
        return Complex(-Re, -Im);
    }

    friend Complex operator+(const double &Re, const Complex &c);
    friend Complex operator-(const double &Re, const Complex &c);
    friend Complex operator*(const double &Re, const Complex &c);
    friend Complex operator/(const double &Re, const Complex &c);

    friend double abs(const Complex &c)
    {
        return std::sqrt(c.Re * c.Re + c.Im * c.Im);
    }

    friend std::ostream &operator<<(std::ostream &out, const Complex &c)
    {
        if (c.Re)
        {
            out << std::setfill('0') << std::fixed << std::setprecision(2) << c.Re;
            if (c.Im > 0)
            {
                out << " + " << std::setfill('0') << std::fixed << std::setprecision(2) << c.Im << "i";
            }
            else if (c.Im == 0)
            {
            }
            else
            {
                out << " - " << std::setfill('0') << std::fixed << std::setprecision(2) << -c.Im << "i";
            }
        }
        else
        {
            if (c.Im)
            {
                out << std::setfill('0') << std::fixed << std::setprecision(2) << c.Im << "i";
            }
            else if (c.Im == 0)
            {
                out << "0.00";
            }
        }
        return out;
    }
};

Complex operator+(const double &Re, const Complex &c)
{
    return Complex(Re + c.Re, c.Im);
}

Complex operator-(const double &Re, const Complex &c)
{
    return Complex(Re - c.Re, -c.Im);
}

Complex operator*(const double &Re, const Complex &c)
{
    return Complex(Re * c.Re, Re * c.Im);
}

Complex operator/(const double &Re, const Complex &c)
{
    double denominator = c.Re * c.Re + c.Im * c.Im;
    double new_Re = (Re * c.Re) / denominator;
    double new_Im = (-Re * c.Im) / denominator;
    return Complex(new_Re, new_Im);
}

Complex operator"" i(unsigned long long Im)
{
    return Complex(0, static_cast<double>(Im));
}

Complex operator"" i(long double Im)
{
    return Complex(0, static_cast<double>(Im));
}
