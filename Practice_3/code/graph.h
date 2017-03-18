#pragma once
#include <QString>
#include "qcustomplot_lib/qcustomplot.h"

//=============================================================================
class Graph
{
public:
    Graph();
    Graph(QCustomPlot *area);

    enum Type { Line, Bar };

    void                    draw(QColor color = QColor(103, 21, 153));
    void                    clear();
    void                    showHalf(bool sh = true);
    void                    showCount(int n);
    void                    savePng(const QString &name, const QString &dir = "");

    void                    setSecond(QVector<double> p);
    void                    setDrawType(Type t);
    void                    setPoints(QVector<double> p);
    void                    setXYAxisName(const QString &xn, const QString &yn);

    double                  getMin() const;
    double                  getMax() const;
    const QVector<double> & getPoints() const;

private:
    QVector<double> _points;
    QCustomPlot *_area;
    Type _type;

    // make both graphics size is equal - прореживание
    void _makeGraphSizeEqual(QVector<double> &g1, QVector<double> &g2);
};

