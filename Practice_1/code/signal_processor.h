#pragma once

#include <QVector>
#include <QMap>
#include <QtMath>

#include <cmath>
#include <chrono>
#include <random>

#include <QDebug>

//=============================================================================
struct SignalProcessor
{   
    /* Returns an array of N values with normal distribution in min..max range */
    QVector<double> getGaussianNoise(const double minV, const double maxV, const int N);

    /* Returns an array of N values of analyzed signal */
    QVector<double> getSignal(int count, double step, double alfa, double beta, double sigma, double mu);

    /* Returns an array of N values of the signal histogram */
    QVector<double> createHistogram(const QVector<double>& signal, const int N);

    /* It calculates the value of the signal entropy wiyh probability distribution */
    double calculateTheEntropy (const QVector<double>& pd);

    /* It combines the two signals. Steps of both signals must be equal */
    QVector<double> combineSignals(const QVector<double>& signal1, const QVector<double>& signal2 );

    /* Returns an array of signal сonvolution. Steps of both signals must be equal */
    QVector<double> createConvolution (const QVector<double>& signal1, const QVector<double>& signal2);

private:
    const double _PI = 3.14159265358979323846;
    double _functionSk(int k, int count, double step, double alfa, double beta, double sigma, double mu);
};
