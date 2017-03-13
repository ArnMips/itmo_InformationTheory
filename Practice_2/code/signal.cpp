#include "signal.h"


QVector<double> Signal::createGaussian(double deviation, int n)
{
    const double PI = 3.141592653589793;
    const double RANGE = 5; // x == (-REANGE..+REANGE)
    const double STEP = (RANGE * 2) / (n - 1);
    double x = -RANGE;

    QVector<double> s(n);
    for (double &it : s) {
        it = 1 / (deviation * sqrt(2 * PI)) * exp(- x*x / (2 * pow(deviation,2)));
        x += STEP;
    }
    return std::move(s);
}

QVector<double> Signal::createImpuls(double alfa, double beta, double mu, double sigma, double dx, int n)
{
    const double PI = 3.141592653589793;
    QVector<double> s(n);

    for (int k(0); k < n; ++k) {
        double x = dx * k;
        double A = beta + alfa/(sigma * sqrt(2 * PI)) * exp(- pow(x - mu, 2) / (2 * pow(sigma,2)));
        double F = pow(x - n * dx / 2, 2) / 20;
        s[k] = A * cos(F);
    }
    return std::move(s);
}
