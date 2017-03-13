#pragma once
#include <math.h>

//=============================================================================
class ComplexNum
{
public:
    ComplexNum();
    ComplexNum(double re, double im = 0);

    double re();
    double im();
    double abs();

    ComplexNum operator+ (const ComplexNum &);
    ComplexNum operator- (const ComplexNum &);
    ComplexNum operator* (const ComplexNum &);
    ComplexNum operator/ (const ComplexNum &);
    ComplexNum operator+=(const ComplexNum &);
    bool       operator==(const ComplexNum &);

private:
    double _re;
    double _im;
};

