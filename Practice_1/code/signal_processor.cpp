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

QVector<double> SignalProcessor::getTriangle(const int count)
{
    QVector<double> arr(count);
    for (int i = 0; i < count; ++i) {
        if (i <= qFloor(count / 2)) {
            arr[i] =  i / 5;
        } else {
            arr[i] = (count - 1 - i) / 5;
        }
    }
    return arr;
}

QVector<double> SignalProcessor::createHistogram(const QVector<double>& signal, const double m, QString type)
{
    double minY = *std::min_element(signal.constBegin(), signal.constEnd());
    double maxY = *std::max_element(signal.constBegin(), signal.constEnd());
    double step;
    int n;

    if (type == "count") {
        n = m;
        step = qAbs(maxY - minY) / (n - 1);
    } else if (type == "step") {
        n = qFloor(qAbs(maxY - minY) / m) + 1;
        step = m;
    } else { throw; }

    QVector<double> hist(n);
    for (int i = 0; i < signal.size(); ++i) {
        double index = qFloor((signal.at(i) - minY) / step);
        ++hist[index];

    }
    return hist;
}

double SignalProcessor::calculateTheEntropy(const QVector<double>& pd)
{
    double entropy(0);

    for (int i(0); i < pd.size(); ++i) {
        entropy += (pd.at(i) == 0) ? (0) : (pd.at(i) * qLn(pd.at(i)) / qLn(2));
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

QVector<double> SignalProcessor::createConvolution(const QVector<double>& signal1, const QVector<double>& signal2)
{
    int N1 = signal1.size();
    int N2 = signal2.size();
    int M = N1 + N2 - 1;

    QVector<double> conv(M, 0);

    for (int i = 0; i < M; i++) {
        //if (i % 2 == 0) { continue; }
        for(int j = qMax(0, i-M+1); j <= qMin(i, M-1); j++) {
            double s1 = (    (j < 0) ||     (j >= N1)) ? 0 : signal1.at(j);
            double s2 = ((i - j < 0) || (i - j >= N2)) ? 0 : signal2.at(i-j);
            conv[i] += s1 * s2;
        }
    }
    return conv;
}
