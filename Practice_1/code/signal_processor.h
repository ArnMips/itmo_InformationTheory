#pragma once

#include <QVector>
#include <QtMath>
#include <chrono>
#include <random>

//=============================================================================
struct SignalProcessor
{   
    /* Returns an array of N values with normal distribution in min..max range */
    QVector<double> getGaussianNoise(const int count, const double mean, const double deviation);

    /* Returns an array of N values of analyzed signal */
    QVector<double> getSignal(int count, double step, double alfa, double beta, double sigma, double mu);

    QVector<double> getTriangle(const int count);

    /* Returns an array of N values of the signal histogram */
    QVector<double> createHistogram(const QVector<double> &signal, const double m, QString type = "count"); // "step" or "count" : 'type' of 'm'

    /* It calculates the value of the signal entropy wiyh probability distribution */
    double calculateTheEntropy (const QVector<double> &pd);

    /* It combines the two signals. Steps of both signals must be equal */
    QVector<double> combineSignals(const QVector<double> &signal1, const QVector<double> &signal2 );

    /* Returns an array of signal сonvolution. Steps of both signals must be equal */
    QVector<double> createConvolution (const QVector<double> &signal1, const QVector<double> &signal2);

private:
    const double _PI = 3.14159265358979323846;
};
