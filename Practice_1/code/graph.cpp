#include "graph.h"

void Graph::drawLineGraph(QCustomPlot *graph, QVector<double> x, QVector<double> y)
{
    double minX = *std::min_element(x.constBegin(), x.constEnd());
    double maxX = *std::max_element(x.constBegin(), x.constEnd());
    double minY = *std::min_element(y.constBegin(), y.constEnd());
    double maxY = *std::max_element(y.constBegin(), y.constEnd());

    graph->clearGraphs();
    graph->addGraph();
    graph->graph(0)->setData(x, y);
    graph->xAxis->setRange(minX, maxX);
    graph->yAxis->setRange(minY, maxY);
    graph->replot();
}

void Graph::drawBarGraph(QCustomPlot *graph, QVector<double> x, QVector<double> y)
{
    double minX = *std::min_element(x.constBegin(), x.constEnd());
    double maxX = *std::max_element(x.constBegin(), x.constEnd());
    double minY = *std::min_element(y.constBegin(), y.constEnd());
    double maxY = *std::max_element(y.constBegin(), y.constEnd());

    graph->clearGraphs();

    QCPBars *newBars = new QCPBars(graph->xAxis, graph->yAxis);
    newBars->setData(x, y);
    //newBars->setWidth();

    graph->xAxis->setRange(minX, maxX);
    graph->yAxis->setRange(minY, maxY);
    graph->replot();
}
