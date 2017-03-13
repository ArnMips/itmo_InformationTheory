#pragma once
#include <QVector>

///============================================================================
namespace Signal {
QVector<double> createImpuls(double alfa, double beta, double mu, double sigma, double dx, int n);
QVector<double> createGaussian(double deviation, int n);
}
