#include "signalscreator.h"


QList<qreal> SignalsCreator::getGaussianNoise
    ( const double minValue
    , const double maxValue
    , const int numOfValues
    )
{
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);
      std::normal_distribution<double> distribution (0.0,1);//0.0 0.25


    QList<qreal> points;
    double maxR(0);
    for (int i(0); i < numOfValues; ++i) {
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

QList<qreal> SignalsCreator::getSpecialSignal (const double step)
{
    _step = step; //count number

    QList<qreal> points;
    for (int i(0); i < step; ++i ){
        points.push_back(_functionSk(i));
    }
    return points;
}

QList<QPointF> SignalsCreator::createHistogram(const QList<QPointF> &signal, const double step)
{
    //Шаг в массиве signal.x должен быть кратен steps

    double minY(INFINITY), maxY(0);
    for (int i(0); i < signal.size(); ++i) {
        minY = signal.at(i).y() < minY ? signal.at(i).y() : minY;
        maxY = signal.at(i).y() > maxY ? signal.at(i).y() : maxY;
    }

    QVector<QPointF> hist;
    int reserveSize = qCeil(qAbs(maxY - minY) / step);
    hist.resize(reserveSize);

    double val(minY);
    for (int i = 0; i < hist.size(); ++i) {
        hist[i] = QPointF(val, 0);
        val += step;
    }

    int index(0);
    for (int i = 0; i < signal.size(); ++i) {
        index = qFloor((signal.at(i).y()+qAbs(minY)) / step);
        hist[index].ry()++;
    }

    return hist.toList();
}

QList<QPointF> SignalsCreator::combineSignals(const QList<QPointF> &signal1, const QList<QPointF> &signal2)
{
    int size = qMin(signal1.size(), signal2.size());

    QList<QPointF> newSignal;
    for (int i = 0; i < size; ++i) {
        newSignal.push_back(signal1.at(i) + signal2.at(i));
        //newSignal[i].rx() /= 2;
        //newSignal[i].ry() /= 2;
    }
    return newSignal;
}

double SignalsCreator::_functionFk(const double k)
{
    double x = _DELTAx * k;
    return qPow(x - _step * _DELTAx / 2, 2) / 20;
}

double SignalsCreator::_functionAk(const double k)
{
    double x = _DELTAx * k;
    return 500/(10 * qSqrt(2 * _PI)) * qExp(- qPow(x - 50, 2) / (2*10*10));
}

double SignalsCreator::_functionSk(const double k)
{
    return _functionAk(k) * qCos(_functionFk(k));
}
