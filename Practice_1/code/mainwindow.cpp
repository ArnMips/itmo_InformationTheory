#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    ui->lbl_signalentropyValue->setText("Histogram isn't load");
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
    ui->line_signalHistCount->setText("1000");
}

void MainWindow::on_btn_signalHistLoad_clicked()
{
    if (_signal.isEmpty()) {
        ui->lbl_signalHistError->show();
        return;
    }
    ui->lbl_signalHistError->hide();
    int countHist = ui->line_signalHistCount->text().toInt();
    int countSignal = ui->line_signalCount->text().toInt();

    //create histogram
    _signalHist  = _signalProc.createHistogram(_signal, countHist);
    QVector<double> x = _fillAray(0, countHist, 1);
    Graph::drawBarGraph(ui->wdg_signalHist, x, _signalHist);

    //calculate table
    ui->tblWdg_signalHist->setRowCount(countHist);
    ui->tblWdg_signalHist->setColumnCount(1);

    QVector<double> pd(countHist); // probability distribution
    for (int i(0); i < countHist; ++i) {
        pd[i] = _signalHist[i] / countSignal;
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
    ui->lbl_noiseEntropyVal->setText("Histogram isn't load");
}

void MainWindow::on_btn_noiseHistLoat_clicked()
{
    if (_noise.isEmpty()) {
        ui->lbl_noiseHistError->show();
        return;
    }
    ui->lbl_noiseHistError->hide();
    int countHist = ui->line_noiseHistCount->text().toInt();
    int countNoise = ui->line_noiseCount->text().toInt();

    //create noise histogram
    _noiseHist = _signalProc.createHistogram(_noise, countHist);
    QVector<double> x = _fillAray(0, countHist, 1);
    Graph::drawBarGraph(ui->wdg_noiseHist, x, _noiseHist);

    //calculate noise table
    ui->tbl_noiseHistProbability->setRowCount(countHist);
    ui->tbl_noiseHistProbability->setColumnCount(1);

    QVector<double> pd(countHist); // probability distribution
    for (int i(0); i < countHist; ++i) {
        pd[i] = _noiseHist[i] / countNoise;
        QString item = QString::number(pd[i]);
        ui->tbl_noiseHistProbability->setItem(i, 0, new QTableWidgetItem(item));
    }

    //calculate noise entropy
    double noiseEntropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_noiseEntropyVal->setText(QString::number(noiseEntropy));

}

void MainWindow::on_btn_noiseHistReset_clicked()
{
    ui->line_noiseHistCount->setText("1000");
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

    ui->text_signalNoiseErrorLoad->hide();
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
    ui->tbl_signalNoiseProbability->setRowCount(histCount);
    ui->tbl_signalNoiseProbability->setColumnCount(1);

    QVector<double> pd(histCount); // probability distribution
    for (int i(0); i < histCount; ++i) {
        pd[i] = _combSingnalsHist[i] / combSingnalsCount;
        QString item = QString::number(pd[i]);
        ui->tbl_signalNoiseProbability->setItem(i, 0, new QTableWidgetItem(item));

    }

    ///signal+noise entropy --------------------------------------
    double entropy  = _signalProc.calculateTheEntropy(pd);
    ui->lbl_signalNoiseEntropyVal->setText(QString::number(entropy));

    ///convolution -----------------------------------------------
    QVector<double> _convolution = _signalProc.createConvolution(_signal, _noise);
    Graph::drawLineGraph(ui->wdg_signalNoiseConvolution, x2, _convolution);
}
