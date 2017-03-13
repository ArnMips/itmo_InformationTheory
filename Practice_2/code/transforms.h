#pragma once

#include "complexnum.h"
#include "signal.h"
#include <QVector>

///============================================================================
namespace Transform {
QVector<double> blur(const QVector<double> &s, int n, double d, bool saveExtremeValues = false);
QVector<ComplexNum> DTF(const QVector<double> &s);
QVector<double> combine(const QVector<double> &s1, const QVector<double> &s2);

}

