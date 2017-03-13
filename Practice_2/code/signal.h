#pragma once
#include <QVector>

///============================================================================
namespace Signal {
QVector<double> createImpuls(double alfa, double beta, double mu, double sigma, double dx, int n);
QVector<double> createGaussian(double deviation, int n);
QVector<double> createSin(const int n, const int t);
QVector<double> createGaussianNoise(const int count, const double deviation, const double mean = 0.0);
}
