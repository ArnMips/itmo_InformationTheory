#pragma once
#include <math.h>
#include <QVector>

//=============================================================================
class ComplexNum
{
public:
    ComplexNum();
    ComplexNum(double re, double im = 0);

    double re() const;
    double im() const;
    double abs() const;
    ComplexNum conj() const; //is Complex conjugate

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

QVector<double> toRe(const QVector<ComplexNum> &);
QVector<double> toIm(const QVector<ComplexNum> &);
QVector<double> toAbs(const QVector<ComplexNum> &);

QVector<double> spectDensity(const QVector<QVector<ComplexNum> > &);

