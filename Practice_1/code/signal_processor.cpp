#include "signal_processor.h"


QVector<double> SignalProcessor::getGaussianNoise(const double minV, const double maxV, const int N)
{
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);
      std::normal_distribution<double> distribution (0.0,1.0);//0.0 0.25

    QVector<double> points;
    double maxR(0);
    for (int i(0); i < N; ++i) {
        //double val =  2 * ((rand()/((double)RAND_MAX)) - 0.5);
        //double val = minValue + (maxValue - minValue) / RAND_MAX * std::rand();
        //double val =  minValue + (maxValue - minValue) / distribution.max() * distribution(generator);
        double val = distribution(generator);
        points.push_back(val);
     //   maxR = val > maxR ? val : maxR;
    }
//    for (int i(0); i < points.size(); ++i) {
//        points[i] = points[i] / maxR * (maxValue - minValue) + minValue;
//    }

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
    for (int i(0); i < signal.size(); ++i) {
        minY = signal.at(i) < minY ? signal.at(i) : minY;
        maxY = signal.at(i) > maxY ? signal.at(i) : maxY;
    }

    double step = qAbs(maxY - minY) / N;

    QVector<double> hist(N);
    for (int i = 0; i < N; ++i) {
        int index = qFloor((signal.at(i) - minY) / step);
        hist[index]++;
    }

    return hist;
}

double SignalProcessor::calculateTheEntropy(const QVector<double> &pd)
{
    double entropy(0);

    for (int i(0); i < pd.size(); ++i) {
        double s = pd.at(i);
        entropy += s * qLn(s);
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

double SignalProcessor::_functionSk(int k, int count, double step, double alfa, double beta, double sigma, double mu)
{
    double x = step * k;
    double A = alfa/(sigma * qSqrt(2 * _PI)) * qExp(- qPow(x - mu, 2) / (2*sigma*sigma));
    double F = qPow(x - count * step / 2, 2) / 20;

    return A * qCos(F);
}
