#include "graphics.h"

Graphics::Graphics(QList<QPointF> points, QWidget* parent)
    : QWidget(parent)
    , _chart(new QChart())
{
    updateChart(points);

    //_chart->createDefaultAxes();
    //_chart->axisX()->setRange(0, points.size()); // points.size() == maxX
    //_chart->axisY()->setRange(-20, 20);

    QChartView *chartView = new QChartView(_chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(chartView);

    parent->setLayout(layout);
}

void Graphics::updateChart(QList<QPointF> points)
{
    QLineSeries *series = new QLineSeries();
    series->replace(points);

    _chart->addSeries(series);

    double minY(INFINITY), maxY(0), minX(INFINITY), maxX(0);
    for (int i(0); i < points.size(); ++i) {
        minY = points.at(i).y() < minY ? points.at(i).y() : minY;
        maxY = points.at(i).y() > maxY ? points.at(i).y() : maxY;
        minX = points.at(i).x() < minX ? points.at(i).x() : minX;
        maxX = points.at(i).x() > maxX ? points.at(i).x() : maxX;
    }

    _chart->legend()->hide();
    _chart->createDefaultAxes();
    _chart->axisX()->setRange(minX, maxX); // points.size() == maxX
    _chart->axisY()->setRange(minY, maxY);
}
