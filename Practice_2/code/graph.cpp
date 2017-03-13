#include "graph.h"


Graph::Graph(const QString n, QCustomPlot *pArea, Graph::Type t, QVector<double> s)
    :_name(n), _pArea(pArea), _type(t), _signal(std::move(s))
{}

void Graph::reset(const QVector<double> &s)
{
    _signal = s;
    draw();
}

QString Graph::getName() const
{
    return _name;
}

Graph::Type Graph::getType() const
{
    return _type;
}

double Graph::getMin() const
{
    return *std::min_element(_signal.constBegin(), _signal.constEnd());
}

double Graph::getMax() const
{
    return *std::max_element(_signal.constBegin(), _signal.constEnd());
}


int Graph::getCount() const
{
    return _signal.size();
}

const QVector<double> &Graph::getSignal() const
{
    return _signal;
}

void Graph::draw()
{
    const int MIN_X = 0, MAX_X = _signal.size()-1;
    QVector<double> x(_signal.size(),0);
    for (int i = 0; i < x.size(); ++i) { x[i] = i; }

    _pArea->clearPlottables();
    switch (this->_type) {
    case Line :
        _pArea->addGraph();
        _pArea->graph()->setData(x, _signal);
        _pArea->graph()->setPen(QColor(250, 170, 20));
        break;
    case Bar :
        QCPBars *nB = new QCPBars(_pArea->xAxis, _pArea->yAxis);
        nB->setData(x, _signal);
        nB->setPen(QColor(250, 170, 20));
        nB->setBrush(QColor(250, 170, 20));
        break;
    }
    _pArea->xAxis->setRange(MIN_X, MAX_X);
    _pArea->yAxis->setRange(this->getMin(), this->getMax());
    _pArea->replot();

}


