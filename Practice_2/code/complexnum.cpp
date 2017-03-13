#include "complexnum.h"

ComplexNum::ComplexNum()
    : _re(0), _im(0)
{
}

ComplexNum::ComplexNum(double re, double im)
    : _re(re), _im(im)
{
}

double ComplexNum::re()
{
    return _re;
}

double ComplexNum::im()
{
    return _im;
}

double ComplexNum::abs()
{
    return sqrt(pow(_re, 2) + pow(_im, 2));
}

ComplexNum ComplexNum::operator+(const ComplexNum &x)
{
    return ComplexNum(_re + x._re, _im + x._im);
}

ComplexNum ComplexNum::operator-(const ComplexNum &x)
{
    return ComplexNum(_re - x._re, _im - x._im);
}

ComplexNum ComplexNum::operator*(const ComplexNum &x)
{
    ComplexNum r;
    r._re = _re * x._re - _im * x._im;
    r._im = _im * x._re + _re * x._im;
    return r;
}

ComplexNum ComplexNum::operator/(const ComplexNum &x)
{
    ComplexNum r;
    r._re = (_re * x._re + _im * x._im) / (pow(x._re, 2) + pow(x._im, 2));
    r._im = (_im * x._re - _re * x._im) / (pow(x._re, 2) + pow(x._im, 2));
    return r;
}

ComplexNum ComplexNum::operator+=(const ComplexNum &x)
{
    _re += x._re;
    _im += x._im;

    return *this;
}

bool ComplexNum::operator==(const ComplexNum &x)
{
    return (_re == x._re) && (_im == x._im);
}

