#pragma once
#include "qcustomplot_lib/qcustomplot.h"
#include <QVector>
#include <QString>

///============================================================================
namespace Graph {

enum Type { Line, Bar };
void draw(QCustomPlot *pArea, const QVector<double> &s, Type t);
}
