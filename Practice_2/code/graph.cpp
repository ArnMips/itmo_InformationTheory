#include "graph.h"

void Graph::draw(QCustomPlot *pArea, const QVector<double> &s, Type t)
{
    QVector<double> x( s.size(), 0 );
    for (int i = 0; i < x.size(); ++i) { x[i] = i; }

    pArea->clearPlottables();
    pArea->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QColor color(103, 21, 153);

    switch (t) {
    case Line :
        pArea->addGraph();
        pArea->graph()->setData(x, s);
        pArea->graph()->setPen(color);
        break;
    case Bar :
        QCPBars *nB = new QCPBars(pArea->xAxis, pArea->yAxis);
        nB->setData(x, s);
        nB->setPen(color);
        nB->setBrush(color);
        break;
    }

    int minX = 0;
    int maxX = s.size() -1;
    double minY = *std::min_element(s.begin(), s.end());
    double maxY = *std::max_element(s.begin(), s.end());

    pArea->xAxis->setRange(minX, maxX);
    pArea->yAxis->setRange(minY, maxY);

    pArea->replot();
}


