#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mainFunction();

    // Graphics defaut setting
    on_btn_signalReset_clicked();
    on_btn_signalHistReset_clicked();
    on_btn_hoiseReset_clicked();
    on_btn_noiseHistReset_clicked();

    ui->text_signalNoiseErrorLoad->hide();
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

void MainWindow::on_btn_signalLoad_clicked()
{
    int count    = ui->line_signalCount->text().toInt();
    double step  = ui->line_signalStep->text().toDouble();
    double alfa  = ui->line_signalAlfa->text().toDouble();
    double beta  = ui->line_signalBeta->text().toDouble();
    double sigma = ui->line_signalSigma->text().toDouble();
    double mu    = ui->line_signalMu->text().toDouble();

    _signal           = _signalProc.getSignal(count, step, alfa, beta, sigma, mu);
    QVector<double> x = _fillAray(0, count, 1);

    Graph::drawLineGraph(ui->wdg_signalGraph, x, _signal);
    ui->lbl_signalentropyValue->setText("Histogram is not load");
}

void MainWindow::on_btn_signalReset_clicked()
{
    ui->line_signalStep->setText("0.1");
    ui->line_signalCount->setText("1000");
    ui->line_signalAlfa->setText("500");
    ui->line_signalBeta->setText("1");
    ui->line_signalSigma->setText("10");
    ui->line_signalMu->setText("50");

    ui->lbl_signalHistError->hide();
}

void MainWindow::on_btn_signalHistReset_clicked()
{
    ui->line_signalHistCount->setText("999"); // магия, если ввести сюда 1000 - не работает
}

void MainWindow::on_btn_signalHistLoad_clicked()
{
    if (_signal.isEmpty()) {
        ui->lbl_signalHistError->show();
        return;
    }
    ui->lbl_signalHistError->hide();
    int count = ui->line_signalHistCount->text().toInt();

    //create histogram
    _signalHist  = _signalProc.createHistogram(_signal, count);
    QVector<double> x = _fillAray(0, count, 1);
    Graph::drawBarGraph(ui->wdg_signalHist, x, _signalHist);

    //calculate table
    ui->tblWdg_signalHist->setRowCount(count);
    ui->tblWdg_signalHist->setColumnCount(1);

    QVector<double> pd(count); // probability distribution
    for (int i(0); i < count; ++i) {
        pd[i] = _signalHist[i] / count;
        QString item = QString::number(pd[i]);
        ui->tblWdg_signalHist->setItem(i, 0, new QTableWidgetItem(item));
    }

    //calculate entropy
    double signalEntropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_signalentropyValue->setText(QString::number(signalEntropy));
}

void MainWindow::on_btn_hoiseReset_clicked()
{
    ui->line_noiseCount->setText("1000");
    ui->line_noiseMean->setText("0");
    ui->line_noiseDeviation->setText("1");

    ui->lbl_noiseHistError->hide();
}

void MainWindow::on_btn_noiseLoad_clicked()
{
    int count        = ui->line_noiseCount->text().toInt();
    double deviation = ui->line_noiseDeviation->text().toDouble();
    double mean      = ui->line_noiseMean->text().toDouble();

    _noise = _signalProc.getGaussianNoise(count, mean, deviation);
    QVector<double> x = _fillAray(0, count, 1);

    Graph::drawLineGraph(ui->wdg_noise, x, _noise);
    ui->lbl_noiseEntropyVal->setText("Histogram is not load");
}

void MainWindow::on_btn_noiseHistLoat_clicked()
{
    if (_noise.isEmpty()) {
        ui->lbl_noiseHistError->show();
        return;
    }
    ui->lbl_noiseHistError->hide();
    int count = ui->line_noiseHistCount->text().toInt();

    //create noise histogram
    _noiseHist = _signalProc.createHistogram(_noise, count);
    QVector<double> x = _fillAray(0, count, 1);
    Graph::drawBarGraph(ui->wdg_noiseHist, x, _noiseHist);

    //calculate noise table
    ui->tbl_noiseHistProbability->setRowCount(count);
    ui->tbl_noiseHistProbability->setColumnCount(2);

    QVector<double> pd(count); // probability distribution
    for (int i(0); i < count; ++i) {
        pd[i] = _noiseHist[i] / count;

        QString item1 = QString::number(x[i]);
        QString item2 = QString::number(pd[i]);

        ui->tbl_noiseHistProbability->setItem(i, 0, new QTableWidgetItem(item1));
        ui->tbl_noiseHistProbability->setItem(i, 1, new QTableWidgetItem(item2));
    }

    //calculate noise entropy
    double noiseEntropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_noiseEntropyVal->setText(QString::number(noiseEntropy));

}

void MainWindow::on_btn_noiseHistReset_clicked()
{
    ui->line_noiseHistCount->setText("999");
}

void MainWindow::on_btn_signalNoiseLoad_clicked()
{
    ui->text_signalNoiseErrorLoad->clear();
    bool error(false);

    if (_signal.isEmpty()) {
        ui->text_signalNoiseErrorLoad->insertPlainText("Load the signal\n");
    }
    if (_signalHist.isEmpty()) {
        ui->text_signalNoiseErrorLoad->insertPlainText("Load the signal hist\n");
    }
    if (_noise.isEmpty()) {
        ui->text_signalNoiseErrorLoad->insertPlainText("Load the noise\n");
    }
    if (_noiseHist.isEmpty()) {
        ui->text_signalNoiseErrorLoad->insertPlainText("Load the noise hist\n");
    }
    if (_signal.isEmpty() || _signalHist.isEmpty() || _noise.isEmpty() || _noiseHist.isEmpty()) {
        ui->text_signalNoiseErrorLoad->show();
        error = true;
    }
    if (_signal.size() != _noise.size()){
        ui->text_signalNoiseErrorLoad->insertPlainText("Both signal's `count` must be equal\n");
        error = true;
    }
    if (_signalHist.size() != _noiseHist.size()){
        ui->text_signalNoiseErrorLoad->insertPlainText("Both signal's histogram `count` must be equal\n");
        error = true;
    }
    if (error) {
        ui->text_signalNoiseErrorLoad->show();
        return;
    }
    //----------------------------------------------------------------------------

    /// signal+noise graph ---------------------------------------
    QVector<double> _combSingnals = _signalProc.combineSignals(_signal, _noise);
    int combSingnalsCount = _signal.size();
    QVector<double> x1 = _fillAray(0, combSingnalsCount, 1);
    Graph::drawLineGraph(ui->wdg_signalNoise, x1, _combSingnals);

    /// signal+noise histogram -----------------------------------
    int histCount = ui->line_signalNoiseHistCount->text().toInt();
    QVector<double> _combSingnalsHist = _signalProc.createHistogram(_combSingnals, histCount);
    QVector<double> x2 = _fillAray(0, histCount, 1);
    Graph::drawBarGraph(ui->wdg_signalNoiseHist, x2, _combSingnalsHist);

    /// calculate probability table ------------------------------
    ui->tblWdg_signalHist->setRowCount(histCount);
    ui->tblWdg_signalHist->setColumnCount(2);

    QVector<double> pd(histCount); // probability distribution
    for (int i(0); i < histCount; ++i) {
        pd[i] = _combSingnalsHist[i] / histCount;

        QString item1 = QString::number(x2[i]);
        QString item2 = QString::number(pd[i]);

        ui->tbl_signalNoiseProbability->setItem(i, 0, new QTableWidgetItem(item1));
        ui->tbl_signalNoiseProbability->setItem(i, 1, new QTableWidgetItem(item2));
    }

    ///signal+noise entropy --------------------------------------
    double entropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_signalNoiseEntropyVal->setText(QString::number(entropy));

    ///convolution -----------------------------------------------
    QVector<double> _convolution = _signalProc.createConvolution(_signal, _noise);
    Graph::drawLineGraph(ui->wdg_signalNoiseConvolution, x2, _convolution);
}
