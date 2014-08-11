#include "Complex.h"

using namespace std;

ostream &operator <<(ostream &os, const Complex &c1)
{
    os << c1.r_ << " " << c1.i_ << "i" << endl;
    return os;
}

istream &operator >>(istream &is, Complex &c1)
{
    is >> c1.r_ >> c1.i_;
    return is;
}

Complex operator+(const Complex &c1, const Complex &c2)
{
    return Complex(c1.r_ + c2.r_, c1.i_ + c2.i_);
}

Complex operator+(int a, const Complex &c2)
{
    return Complex(c2.r_ + a, c2.i_);
}

Complex operator+(const Complex &c1, int a)
{
    return Complex(c1.r_ + a, c1.i_);
}

Complex operator-(const Complex &c1, const Complex &c2)
{
    return Complex(c1.r_ - c2.r_, c1.i_ - c2.i_);
}

Complex operator-(int a, const Complex &c2)
{
    return Complex(c2.r_ - a, c2.i_);
}

Complex operator-(const Complex &c1, int a)
{
    return Complex(c1.r_ - a, c1.i_);
}

Complex operator*(const Complex &c1, const Complex &c2)
{
     int r = (c1.r_)*(c2.r_) - (c1.i_)*(c2.i_);
     int i = (c1.i_)*(c2.r_) + (c1.r_)*(c2.i_);
     return Complex(r, i);
}

Complex operator/(const Complex &c1, const Complex &c2)
{
    int r = ((c1.r_)*(c2.r_) + (c1.i_)*(c2.i_))/(c2.r_*c2.r_+c2.i_*c2.i_);
    int i = ((c1.i_)*(c2.r_) - (c1.r_)*(c2.i_))/(c2.r_*c2.r_+c2.i_*c2.i_);
    return Complex(r, i);
}

Complex::Complex(const Complex &c)
{
    r_ = c.r_;
    i_ = c.i_;
}

Complex & Complex::operator=(const Complex &c)
{
    r_ = c.r_;
    i_ = c.i_;
    return *this;
}

Complex & Complex::operator=(int a)
{
    r_ = a;
    i_ = 0;
    return *this;
}
