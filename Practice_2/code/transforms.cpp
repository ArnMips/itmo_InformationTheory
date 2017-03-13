#include "transforms.h"

QVector<double> Transform::DTF(const QVector<double> &s)
{
    const double PI = 3.141592653589793;
    const int N = s.size();
    const double F = -2 * PI / N;

    QVector<double> r(N);

    for (int k = 0; k < N; ++k) {
        ComplexNum dtf;
        for (int n = 0; n < N; ++n) {
            double l = F * k * n;
            dtf += ComplexNum(s.at(n)) * ComplexNum(cos(l), sin(l));
        }
        r[k] = dtf.abs();
    }
    return r;
}

QVector<double> Transform::blur(const QVector<double> &s, int n, double d)
{
    QVector<double> gaus = Signal::createGaussian(d, n);

    const int N1 = s.size();
    const int N2 = gaus.size();
    const int M = N1 + N2 - 1;

    QVector<double> r(M, 0);

    for (int i = 0; i < M; i++) {
        for(int j = qMax(0, i-M+1); j <= qMin(i, M-1); j++) {
            double s1 = (    (j < 0) ||     (j >= N1)) ? 0 : s.at(j);
            double s2 = ((i - j < 0) || (i - j >= N2)) ? 0 : gaus.at(i-j);
            r[i] += s1 * s2;
        }
    }
    return r;
}

QVector<double> Transform::combine(const QVector<double> &s1, const QVector<double> &s2)
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
