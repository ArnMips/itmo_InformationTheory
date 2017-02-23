#include "signal_processor.h"


QVector<double> SignalProcessor::getGaussianNoise(const double minV, const double maxV, const int N)
{
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);
      std::normal_distribution<double> distribution (0.0,1);//0.0 0.25


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

QVector<double> SignalProcessor::getSignal(const int N)
{
    _N = N; //count number

    QVector<double> points;
    for (int i(0); i < N; ++i ){
        points.push_back(_functionSk(i));
    }
    return points;
}

QVector<double> SignalProcessor::createHistogram(const QVector<double>& signal, const double step)
{
    double minY(INFINITY), maxY(0);
    for (int i(0); i < signal.size(); ++i) {
        minY = signal.at(i) < minY ? signal.at(i) : minY;
        maxY = signal.at(i) > maxY ? signal.at(i) : maxY;
    }

    int reserveSize = qCeil(qAbs(maxY - minY) / step);
    QVector<double> hist(reserveSize);

    for (int i = 0; i < signal.size(); ++i) {
        int index = qFloor((signal.at(i)+qAbs(minY)) / step);
        hist[index]++;
    }

    return hist;
}

QVector<double> SignalProcessor::combineSignals(const QVector<double>& signal1, const QVector<double>& signal2 )
{
    int size = qMin(signal1.size(), signal2.size());

    QVector<double> newSignal;
    for (int i = 0; i < size; ++i) {
        newSignal.push_back(signal1.at(i) + signal2.at(i));
        //newSignal[i].rx() /= 2;
        //newSignal[i].ry() /= 2;
    }

    return newSignal;
}

double SignalProcessor::_functionFk(const double k)
{
    double x = _DELTA_X * k;
    return qPow(x - _N * _DELTA_X / 2, 2) / 20;
}

double SignalProcessor::_functionAk(const double k)
{
    double x = _DELTA_X * k;
    return 500/(10 * qSqrt(2 * _PI)) * qExp(- qPow(x - 50, 2) / (2*10*10));
}

double SignalProcessor::_functionSk(const double k)
{
    return _functionAk(k) * qCos(_functionFk(k));
}
