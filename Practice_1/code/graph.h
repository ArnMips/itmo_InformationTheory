#pragma once

#include <QWidget>
#include "qcustomplot_lib/qcustomplot.h" //QCustomPlot

///=============================================================================

class Graph {
public:
    void drawLineGraph(QCustomPlot *graph, QVector<double> x, QVector<double> y);
    void drawBarGraph (QCustomPlot *graph, QVector<double> x, QVector<double> y);

};
