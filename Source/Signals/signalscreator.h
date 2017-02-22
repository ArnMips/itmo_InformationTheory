#pragma once

#include <QList>
#include <QPointF>
#include <QtMath>

#include <chrono>
#include <random>

#include <QDebug>

//=============================================================================
struct SignalsCreator
{   

    QList<qreal> getGaussianNoise      (const double minValue
                                       ,const double maxValue
                                       ,const int numOfValues               );

    // return special signal with specified step
    QList<qreal> getSpecialSignal      (const double step                    );

    QList<QPointF> createHistogram     (const QList<QPointF>& signal
                                       ,const double step                   );

    double         calculateTheEntropy (const QList<QPointF>& signal        );

    QList<QPointF> combineSignals      (const QList<QPointF>& signal1
                                       ,const QList<QPointF>& signal2       );

    QList<QPointF> createConvolution   (const QList<QPointF>& signal1
                                       ,const QList<QPointF>& signal2       );

private:
    // special function for signal
    const double _DELTAx = 0.1;  //the sampling step
    const double _PI = 3.14159265358979323846;
    double _step;

    double _functionAk(const double k);
    double _functionFk(const double k);
    double _functionSk(const double k);
};
