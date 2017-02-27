#pragma once

#include <QWidget>
#include "qcustomplot_lib/qcustomplot.h" //QCustomPlot

///=============================================================================

namespace  Graph {
    void drawLineGraph(QCustomPlot *graph, const QVector<double>& x, const QVector<double>& y);
    void drawBarGraph (QCustomPlot *graph, const QVector<double>& x, const QVector<double>& y);
    void setDefaultSettings(QCustomPlot *graph); //type = "Bar" | "Line"
}
