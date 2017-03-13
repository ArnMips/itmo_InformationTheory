#include "graph.h"

void Graph::drawLineGraph(QCustomPlot *graph, const QVector<double>& x, const QVector<double>& y)
{
    double minX = *std::min_element(x.constBegin(), x.constEnd());
    double maxX = *std::max_element(x.constBegin(), x.constEnd());
    double minY = *std::min_element(y.constBegin(), y.constEnd());
    double maxY = *std::max_element(y.constBegin(), y.constEnd());

    graph->clearPlottables();
    graph->addGraph();

    graph->graph()->setData(x, y);
    graph->graph()->setPen(QColor(250, 170, 20));

    graph->xAxis->setRange(minX, maxX);
    graph->yAxis->setRange(minY, maxY);
    graph->replot();
}

void Graph::drawBarGraph(QCustomPlot *graph, const QVector<double>& x, const QVector<double>& y)
{
    double minX = *std::min_element(x.constBegin(), x.constEnd());
    double maxX = *std::max_element(x.constBegin(), x.constEnd());
    double minY = *std::min_element(y.constBegin(), y.constEnd());
    double maxY = *std::max_element(y.constBegin(), y.constEnd());

    graph->clearPlottables();

    QCPBars *newBars = new QCPBars(graph->xAxis, graph->yAxis);
    newBars->setData(x, y);
    newBars->setPen(QColor(250, 170, 20));
    newBars->setBrush(QColor(250, 170, 20));

    graph->xAxis->setRange(minX, maxX);
    graph->yAxis->setRange(minY, maxY);
    graph->replot();
}


void Graph::setDefaultSettings(QCustomPlot *graph)
{
    graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(70, 70, 70));
    gradient.setColorAt(0.38, QColor(85, 85, 85));
    gradient.setColorAt(1, QColor(50, 50, 50));
    graph->setBackground(QBrush(gradient));

    graph->xAxis->setBasePen(QPen(Qt::gray));
    graph->xAxis->setTickLabelColor(Qt::gray);
    graph->xAxis->setTickPen(QPen(Qt::gray));
    graph->xAxis->setSubTickPen(QPen(Qt::gray));
    graph->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    graph->yAxis->setBasePen(QPen(Qt::gray));
    graph->yAxis->setTickPen(QPen(Qt::gray));
    graph->yAxis->setSubTickPen(QPen(Qt::gray));
    graph->yAxis->grid()->setSubGridVisible(true);
    graph->yAxis->setTickLabelColor(Qt::gray);
    graph->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    graph->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
}
