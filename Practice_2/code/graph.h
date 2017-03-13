#pragma once
#include "qcustomplot_lib/qcustomplot.h"
#include <QVector>
#include <QMap>

///============================================================================
class Graph
{
public:
    enum Type { Line, Bar };

    Graph(const QString n, QCustomPlot *pArea, Type t, QVector<double> s = QVector<double>());

    void        reset(const QVector<double> &s);
    void        draw();
    int         getCount() const;
    QString     getName() const;
    Type        getType() const;
    double      getMin() const;
    double      getMax() const;
    const QVector<double> &getSignal() const;

private:

    QCustomPlot     *_pArea;
    QVector<double>  _signal;
    QString _name;
    Type   _type;
};
