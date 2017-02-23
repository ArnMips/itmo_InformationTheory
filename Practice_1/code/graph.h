#pragma once

#include <QWidget>
#include "qcustomplot_lib/qcustomplot.h" //QCustomPlot

///=============================================================================

namespace  Graph {
    void drawLineGraph(QCustomPlot *graph, QVector<double> x, QVector<double> y);
    void drawBarGraph (QCustomPlot *graph, QVector<double> x, QVector<double> y);
}
