#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <stddef.h>
#include <iostream>
#include <math.h>

class Complex
{
    friend std::ostream &operator <<(std::ostream &, const Complex &);
    friend std::istream &operator >>(std::istream &, Complex &);

    friend Complex operator+(const Complex &, const Complex &);
    friend Complex operator+(int, const Complex &);
    friend Complex operator+(const Complex &, int);

    friend Complex operator-(const Complex &, const Complex &);
    friend Complex operator-(int, const Complex &);
    friend Complex operator-(const Complex &, int);

    friend Complex operator*(const Complex &, const Complex &);
    friend Complex operator/(const Complex &, const Complex &);

    public:
        Complex():r_(0), i_(0){};
        Complex(int r, int i):r_(r), i_(i){};
        Complex(const Complex &);
        Complex &operator=(const Complex &);
        Complex &operator=(int);
        double abs()
        {
            return sqrt((r_*r_ + i_*i_));
        }
        
    private:
        int r_;
        int i_;
};

#endif  /*COMPLEX_H_*/
