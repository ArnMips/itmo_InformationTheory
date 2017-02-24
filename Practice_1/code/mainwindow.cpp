#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mainFunction();

    // Graphics defaut setting
    on_pushBtn_signaReset_clicked();
    on_pushBtn_signalHistReset_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_mainFunction()
{

//    /// noise -----------------------------------------------------------------

//    QVector<double> noise       = signalproc.getGaussianNoise(0, 0, N); // TODO:
//    QVector<double> noiseHist   = signalproc.createHistogram(noise, 999);
////TODO:    double noiseEntropy         = signalproc.calculateTheEntropy(noise);

//    x2 = _fillAray(0, noiseHist.size(), 1);

//    Graph::drawLineGraph(ui->widget_3, x1, noise);
//    Graph::drawBarGraph(ui->widget_4, x2, noiseHist);
//    //TODO: write noiseEntropy

//    /// convolution  ----------------------------------------------------------

////TODO:    QVector<double> convolution = signalproc.createConvolution(signal, noise);

////TODO:    Graph::drawLineGraph(ui->widget_5, x, convolution);

//    /// combine singnals  -----------------------------------------------------

//    QVector<double> combSingnals     = signalproc.combineSignals(noise, signal);
//    QVector<double> combSingnalsHist = signalproc.createHistogram(combSingnals, 999);
////TODO:    double combSingnalsEntropy       = signalproc.calculateTheEntropy(combSingnals);

//    x2 = _fillAray(0, combSingnalsHist.size(), 1);

//    Graph::drawLineGraph(ui->widget_5, x1, combSingnals);
//    Graph::drawBarGraph(ui->widget_6, x2, combSingnalsHist);
//    //TODO:    write combSingnalsEntropy
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

void MainWindow::on_pushBtn_signalLoad_clicked()
{
    int count    = ui->line_signalCount->text().toDouble();;
    double step  = ui->line_signalStep->text().toDouble();
    double alfa  = ui->line_signalAlfa->text().toDouble();;
    double beta  = ui->line_signalBeta->text().toDouble();;
    double sigma = ui->line_signalSigma->text().toDouble();;
    double mu    = ui->line_signalMu->text().toDouble();;

    _signal               = _signalProc.getSignal(count, step, alfa, beta, sigma, mu);
    QVector<double> x     = _fillAray(0, count, 1);

    Graph::drawLineGraph(ui->wdg_signalGraph, x, _signal);
}

void MainWindow::on_pushBtn_signaReset_clicked()
{
    ui->line_signalStep->setText("0.1");
    ui->line_signalCount->setText("1000");
    ui->line_signalAlfa->setText("500");
    ui->line_signalBeta->setText("1");
    ui->line_signalSigma->setText("10");
    ui->line_signalMu->setText("50");
}

void MainWindow::on_pushBtn_signalHistReset_clicked()
{
    ui->line_signalHistCount->setText("999"); // магия, если ввести сюда 1000 - не работает
}

void MainWindow::on_pushBtn_signalHistLoad_clicked()
{
    if (_signal.isEmpty()) {
        ui->lbl_signalHistError->setText("Please, load the graph");
        return;
    }
    ui->lbl_signalHistError->clear();
    int count = ui->line_signalHistCount->text().toInt();

    //create histogram
    _signalHist  = _signalProc.createHistogram(_signal, count);
    QVector<double> x = _fillAray(0, count, 1);
    Graph::drawBarGraph(ui->wdg_signalHist, x, _signalHist);

    //calculate table
    ui->tblWdg_signalHist->setRowCount(count);
    ui->tblWdg_signalHist->setColumnCount(2);

    QVector<double> pd(count); // probability distribution
    for (int i(0); i < count; ++i) {
        pd[i] = _signalHist[i] / count;

        QString item1 = QString::number(x[i]);
        QString item2 = QString::number(pd[i]);

        ui->tblWdg_signalHist->setItem(i, 0, new QTableWidgetItem(item1));
        ui->tblWdg_signalHist->setItem(i, 1, new QTableWidgetItem(item2));
    }

    //calculate entropy
    double signalEntropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_signalentropyValue->setText(QString::number(signalEntropy));
}
