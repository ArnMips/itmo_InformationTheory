#include "functions.h"
#include <QtMath>
#include <chrono>
#include <random>

QVector<double> Functions::combine(const QVector<double> &s1, const QVector<double> &s2)
{
    if (s1.size() != s2.size()) {
        throw "Err: 'Transform::combine' size of signals not equal\n";
    }

    const int N = s1.size();
    QVector<double> r(N);

    for (int i = 0; i < N; ++i) {
        r[i] = s1.at(i) + s2.at(i);
    }

    return r;
}

QVector<double> Functions::createGaussianNoise(const int count, const double deviation, const double mean)
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

QVector<double> Functions::addGaussianNoise(const QVector<double> &s, const double deviation, const double mean)
{
    QVector<double> noise = createGaussianNoise(s.size(), deviation, mean);
    return combine(s, noise);
}

QVector<double> Functions::createSignal(double alfa, double beta, double mu, double sigma, double dx, int n)
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

QVector<double> Functions::filtration(const QVector<double> &s, int size)
{
    const int B = size;
    const int N_S = s.size();

    QVector<double> r(N_S, 0);

    for (int k = 0; k < N_S; k++) {
        int a = 0;
        for(int i = -B ; i <= B;  i++) {
            double s1 = ((0 <= k-i) && (k-i < N_S)) ? s.at(k-i) : 0;
            double s2 = (qAbs(i) <= B) ? 1 : 0;
            a += s2;
            r[k] += s1 * s2;
        }
        r[k] /= a;
    }
    return r;
}

QVector<ComplexNum> Functions::DTF(const QVector<double> &s)
{
    const double PI = 3.141592653589793;
    const int N = s.size();
    const double F = -2 * PI / N;

    QVector<ComplexNum> r(N);

    for (int k = 0; k < N; ++k) {
        for (int n = 0; n < N; ++n) {
            double l = F * k * n;
            r[k] += ComplexNum(s.at(n)) * ComplexNum(cos(l), sin(l));
        }
    }
    return r;
}

