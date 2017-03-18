#include "graph.h"
#include <QDebug>

Graph::Graph()
    :_area(nullptr)
{
}

Graph::Graph(QCustomPlot *area)
    :_area(area), _type(Line)
{
}

void Graph::draw(QColor color)
{
    QVector<double> x(_points.size());
    for (int i = 0; i < x.size(); ++i) { x[i] = i; }

    _area->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    switch (_type) {
    case Line :
        _area->addGraph();
        _area->graph()->setData(x, _points);
        _area->graph()->setPen(color);
        break;
    case Bar :
        QCPBars *nB = new QCPBars(_area->xAxis, _area->yAxis);
        nB->setData(x, _points);
        nB->setPen(color);
        nB->setBrush(color);
        break;
    }

    int minX = 0;
    int maxX = _points.size() -1;
    double minY = this->getMin();
    double maxY = this->getMax();

    _area->xAxis->setRange(minX, maxX);
    _area->yAxis->setRange(minY, maxY);
    _area->replot();
}

void Graph::clear()
{
    _area->clearGraphs();
    _area->clearPlottables();
    _area->replot();
    _points.clear();
}

void Graph::showHalf(bool sh)
{
    int to = (sh) ? _points.size() / 2 : _points.size();
    _area->xAxis->setRangeUpper(to);
    _area->replot();
}

void Graph::showCount(int n)
{
    _area->xAxis->setRangeUpper(n);
    _area->replot();
}

void Graph::savePng(const QString &name, const QString &dir)
{
    _area->savePng(dir + name + ".png");
}

void Graph::setSecond(QVector<double> newPoints)
{
    if (_points.isEmpty()) {
        _points = newPoints;
        this->draw(QColor(0, 0, 255, 90));
        return;
    }

    if ((_points.size() != newPoints.size())){
        _makeGraphSizeEqual(_points, newPoints);
    }

    QVector<double> oldPoints = _points;
    this->clear();
    _points = oldPoints;
    this->draw(QColor(255, 0, 0, 90));

    _points = newPoints;
    this->draw(QColor(0, 0, 255, 90));


}

void Graph::setDrawType(Graph::Type t)
{
    _type = t;
}

void Graph::setPoints(QVector<double> p)
{
    this->clear();
    _points = p;
}

void Graph::setXYAxisName(const QString &xn, const QString &yn)
{
    _area->xAxis->setLabel(xn);
    _area->yAxis->setLabel(yn);
}

double Graph::getMin() const
{
    return *std::min_element(_points.constBegin(), _points.constEnd());
}

double Graph::getMax() const
{
    return *std::max_element(_points.constBegin(), _points.constEnd());
}

const QVector<double> &Graph::getPoints() const
{
    return _points;
}

void Graph::_makeGraphSizeEqual(QVector<double> &g1, QVector<double> &g2)
{
    /* все действия ниже производятся с g1,
     * если g1.size() < g2.size() осуществяется swap
     * если swop был ранее он будет произведен еще раз
     */

    bool f = false;
    if (g1.size() < g2.size()) {
        //g1.swap(g2);
        std::swap(g1,g2);
        f = true;
    }

//    int n = g1.size() / g2.size();
//    QVector<double> ns(n);
//    for (int k(0), i(0); i < g2.size(); k+= n, i++) {
//        g1.erase(g1.begin() + k-i);
//    }

    int n = g2.size();
    int k = g1.size() / g2.size();
    QVector<double> ns(n);
    for (int i(0); i < n; i++) {
        ns[i] = g1[i * k];
    }
    g1 = ns;



    qDebug() << g1.size() << " " << g2.size(); //!!!

    g1.resize(g2.size()); //если соответствие неполное

    if (f) {
        g1.swap(g2);
    };
}
