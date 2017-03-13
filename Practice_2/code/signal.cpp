#include "signal.h"
#include <QtMath>
#include <chrono>
#include <random>

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

QVector<double> Signal::createSin(const int n, const int t)
{
    const double PI = 3.141592653589793;
    QVector<double> s(n);

    double step = 2 * PI * t / n;
    double dstep = 0;

    for (int i = 0; i < n ; ++i) {
        s[i] = sin(dstep);
        dstep = (dstep <= 2*PI) ? dstep+step : step;
    }

   return std::move(s);
}

QVector<double> Signal::createGaussianNoise(const int count, const double deviation, const double mean)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(mean, deviation);

    QVector<double> points(count);
    for (int i(0); i < count; ++i) {
        points[i] = distribution(generator);
    }
    return points;
}
