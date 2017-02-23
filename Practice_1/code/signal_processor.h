#pragma once

#include <QVector>
#include <QtMath>

#include <chrono>
#include <random>

#include <QDebug>

//=============================================================================
struct SignalProcessor
{   
    /* Returns an array of N values with normal distribution in min..max range */
    QVector<double> getGaussianNoise(const double minV, const double maxV, const int N);

    /* Returns an array of N values of analyzed signal */
    QVector<double> getSignal(const int N = 1000);

    /* Returns an array of values with a some 'step' of the signal histogram */
    QVector<double> createHistogram(const QVector<double>& signal, const double step);

    /* It calculates the value of the signal entropy */
    double calculateTheEntropy (const QVector<double>& signal);

    /* It combines the two signals. Steps of both signals must be equal */
    QVector<double> combineSignals(const QVector<double>& signal1, const QVector<double>& signal2 );

    /* Returns an array of signal сonvolution. Steps of both signals must be equal */
    QVector<double> createConvolution (const QVector<double>& signal1, const QVector<double>& signal2);

private:
    const double _DELTA_X = 0.1; // the sampling step
    const double _PI = 3.14159265358979323846;
    int _N;

    double _functionAk(const double k);
    double _functionFk(const double k);
    double _functionSk(const double k);
};
