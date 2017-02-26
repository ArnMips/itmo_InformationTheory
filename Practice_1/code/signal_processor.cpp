#include "signal_processor.h"


QVector<double> SignalProcessor::getGaussianNoise(const int count, const double mean, const double deviation)
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

QVector<double> SignalProcessor::getSignal(int count, double step, double alfa, double beta, double sigma, double mu)
{
    QVector<double> points(count);
    for (int k(0); k < count; ++k) {
        double x = step * k;
        double A = beta + alfa/(sigma * qSqrt(2 * _PI)) * qExp(- qPow(x - mu, 2) / (2*sigma*sigma));
        double F = qPow(x - count * step / 2, 2) / 20;
        points[k] = A * qCos(F);
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
        entropy += (pd[i] == 0) ? (0) : (pd[i] * qLn(pd[i]) / qLn(2));
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

QVector<double> SignalProcessor::createConvolution(QVector<double> signal1, QVector<double> signal2)
{
    int nSignal1 = signal1.size();
    int nSignal2 = signal2.size();
    int nConv = nSignal1 + nSignal2 - 1;

    signal1.resize(nConv);
    signal1.insert(nSignal1, nConv - nSignal1, 0.0);
    signal2.resize(nConv);
    signal2.insert(nSignal2, nConv - nSignal2, 0.0);

    QVector<double> conv(nConv);
    for (int i(0); i < nConv; ++i) {
        conv[i] = 0;

         for (int j(0); j <= i; ++j) {
            conv[i] += signal1.at(j) * signal2.at(i - j);
        }
    }
    //conv.resize((nConv + 1 )/ 2);
    return conv;
}
