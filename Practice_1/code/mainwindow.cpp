#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mainFunction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_mainFunction()
{
    const int N(1000);
    const double HIST_STEP(0.1);
    SignalProcessor signalproc;
    QVector<double> x1, x2;

    x1 = _fillAray(0, N, 1);

    /// signal ----------------------------------------------------------------

    QVector<double> signal      = signalproc.getSignal();
    QVector<double> signalHist  = signalproc.createHistogram(signal, HIST_STEP);
//TODO:    double signalEntropy        = signalproc.calculateTheEntropy(signal);

    x2 = _fillAray(0, signalHist.size(), 1);

    Graph::drawLineGraph(ui->widget, x1, signal);
    Graph::drawBarGraph(ui->widget_2, x2, signalHist);
    //TODO: write signalEntropy

    /// noise -----------------------------------------------------------------

    QVector<double> noise       = signalproc.getGaussianNoise(0, 0, N); // TODO:
    QVector<double> noiseHist   = signalproc.createHistogram(noise, HIST_STEP);
//TODO:    double noiseEntropy         = signalproc.calculateTheEntropy(noise);

    x2 = _fillAray(0, noiseHist.size(), 1);

    Graph::drawLineGraph(ui->widget_3, x1, noise);
    Graph::drawBarGraph(ui->widget_4, x2, noiseHist);
    //TODO: write noiseEntropy

    /// convolution  ----------------------------------------------------------

//TODO:    QVector<double> convolution = signalproc.createConvolution(signal, noise);

//TODO:    Graph::drawLineGraph(ui->widget_5, x, convolution);

    /// combine singnals  -----------------------------------------------------

    QVector<double> combSingnals     = signalproc.combineSignals(noise, signal);
    QVector<double> combSingnalsHist = signalproc.createHistogram(combSingnals, HIST_STEP);
//TODO:    double combSingnalsEntropy       = signalproc.calculateTheEntropy(combSingnals);

    x2 = _fillAray(0, combSingnalsHist.size(), 1);

    Graph::drawLineGraph(ui->widget_5, x1, combSingnals);
    Graph::drawBarGraph(ui->widget_6, x2, combSingnalsHist);
    //TODO:    write combSingnalsEntropy
}

QVector<double> MainWindow::_fillAray(const double minV, const double maxV, const double step)
{
    const int N = qCeil(qAbs(maxV - minV) / step);
    QVector<double> arr(N);

    double val(minV);
    for (int i(0); i < N; ++i){
        arr[i] = val;
        val += step;
    }

    return arr;
}

