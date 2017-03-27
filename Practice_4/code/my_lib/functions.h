#pragma once
#include "my_lib/complexnum.h"
#include <QVector>

//=============================================================================
namespace Functions {
QVector<double> combine(const QVector<double> &s1, const QVector<double> &s2);
QVector<double> createGaussianNoise(const int count, const double deviation, const double mean);
QVector<double> createNormalNoise(const int count, const double from, const double to, const double u = 1.0);
QVector<double> addGaussianNoise(const QVector<double> &s, const double deviation, const double mean = 0.0);
QVector<double> addNormalNoise(const QVector<double> &s, const double from, const double to, const double u = 1.0);
QVector<double> createSignal(double alfa, double beta, double mu, double sigma, double dx, int n);
QVector<double> filtration(const QVector<double> &s, int size);
QVector<double> autocovariance (const QVector<double> &s);
QVector<ComplexNum> DTF(const QVector<double> &s);
}

