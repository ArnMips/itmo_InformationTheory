#pragma once

#include <QWidget>
#include <QtCharts>
#include <algorithm>

using namespace QtCharts;

//=============================================================================
class Graphics : public QWidget
{
    Q_OBJECT

public:
    Graphics(QList<QPointF>
            ,QWidget* parent);

public slots:
    void updateChart(QList<QPointF>);

private:
    QChart* _chart;
};
