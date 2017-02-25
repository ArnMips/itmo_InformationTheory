#include "signal_processor.h"


QVector<double> SignalProcessor::getGaussianNoise(const int count, const double mean, const double deviation)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution(mean, deviation);

    QVector<double> points(count);
    for (int i(0); i < count; ++i) {
        points[i] = distribution(generator);
    }

    return points;
}

QVector<double> SignalProcessor::getSignal(int count, double step, double alfa, double beta, double sigma, double mu)
{
    QVector<double> points(count);
    for (int i(0); i < count; ++i) {
        points[i] = _functionSk(i, count, step, alfa, beta, sigma, mu);
    }

    return points;
}

QVector<double> SignalProcessor::createHistogram(const QVector<double>& signal, const int N)
{
    double minY(signal.at(0)), maxY(signal.at(0));
    foreach (double var, signal) {
        minY = var < minY ? var : minY;
        maxY = var > maxY ? var : maxY;
    }
    double step = qAbs(maxY - minY) / (N - 1);

    QVector<double> hist(N);
    for (int i = 0; i < signal.size(); ++i) {
        double index = qFloor((signal[i] - minY) / step);
        ++hist[index];

    }
    return hist;
}

double SignalProcessor::calculateTheEntropy(const QVector<double> &pd)
{
    double entropy(0);

    for (int i(0); i < pd.size(); ++i) {
        entropy += pd[i] == 0 ? 0 : pd[i] * qLn(pd[i]); // ???
    }

    return entropy * (-1);
}

QVector<double> SignalProcessor::combineSignals(const QVector<double>& signal1, const QVector<double>& signal2 )
{
    int size = qMin(signal1.size(), signal2.size());

    QVector<double> newSignal;
    for (int i = 0; i < size; ++i) {
        newSignal.push_back(signal1.at(i) + signal2.at(i));
    }

    return newSignal;
}

QVector<double> SignalProcessor::createConvolution(const QVector<double> &signal1, const QVector<double> &signal2)
{
    int count = signal1.size();
    QVector<double> conv(count);

    for (int i(0); i < count; ++i) {
        for (int m(0); m < i; ++m) {
            conv[i] += signal1.at(m) * signal2.at(i - m);
        }
    }

    return conv;
}

double SignalProcessor::_functionSk(int k, int count, double step, double alfa, double beta, double sigma, double mu)
{
    double x = step * k;
    double A = alfa/(sigma * qSqrt(2 * _PI)) * qExp(- qPow(x - mu, 2) / (2*sigma*sigma));
    double F = qPow(x - count * step / 2, 2) / 20;

    return A * qCos(F);
}
