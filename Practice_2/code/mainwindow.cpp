#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _setDefaultSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pshBtn_signalReset_clicked()
{
    ui->lnEdit_signalStep->setText("0.1");
    ui->lnEdit_signalCount->setText("1000");
    ui->lnEdit_signalAlfa->setText("500");
    ui->lnEdit_signalBeta->setText("1");
    ui->lnEdit_signalSigma->setText("10");
    ui->lnEdit_signalMu ->setText("50");
}

void MainWindow::on_pshBtn_signalLoad_clicked()
{
    int count    = ui->lnEdit_signalCount->text().toInt();
    double step  = ui->lnEdit_signalStep->text().toDouble();
    double alfa  = ui->lnEdit_signalAlfa->text().toDouble();
    double beta  = ui->lnEdit_signalBeta->text().toDouble();
    double sigma = ui->lnEdit_signalSigma->text().toDouble();
    double mu    = ui->lnEdit_signalMu->text().toDouble();

    _signal = (!ui->chkBox_sin->isChecked())
            ? Signal::createImpuls(alfa, beta, mu, sigma, step, count)
            : Signal::createSin(count, 4);


    QVector<ComplexNum> signalDtf = Transform::DTF(_signal);
    QVector<double> signalDtfRe = toRe(signalDtf);
    QVector<double> signalDtfIm = toIm(signalDtf);
    QVector<double> signalDtfAbs = toAbs(signalDtf);

    if (ui->chkBox_signalDtfAbs->isChecked()) {
        signalDtfAbs.resize(signalDtfAbs.size() / 2);
    }

    Graph::draw(ui->wdg_signal, _signal, Graph::Line);
    Graph::draw(ui->wdg_signalDtfRe, signalDtfRe, Graph::Bar);
    Graph::draw(ui->wdg_signalDtfIm, signalDtfIm, Graph::Bar);
    Graph::draw(ui->wdg_signalDtfAbs, signalDtfAbs, Graph::Bar);

}

void MainWindow::on_pshBtn_signalCutReset_clicked()
{
    ui->lnEdit_signalCutFrom->setText("0");
    ui->lnEdit_signalCutTo->setText("0");
}

void MainWindow::on_pshBtn_signalCutLoad_clicked()
{
    int from = ui->lnEdit_signalCutFrom->text().toInt();
    int to   = ui->lnEdit_signalCutTo->text().toInt();

    QVector<double> signalCut(_signal.size());
    for (int i = 0; i < _signal.size(); ++i) {
        signalCut[i] = ((from <= i) && (i <= to)) ? 0 : _signal[i];
    }

    QVector<ComplexNum> signalDtf = Transform::DTF(signalCut);
    QVector<double> signalDtfRe = toRe(signalDtf);
    QVector<double> signalDtfIm = toIm(signalDtf);
    QVector<double> signalDtfAbs = toAbs(signalDtf);

    if (ui->chkBox_signalCutDtfAbs->isChecked()) {
        signalDtfAbs.resize(signalDtfAbs.size() / 2);
    }

    Graph::draw(ui->wdg_signalCut, signalCut, Graph::Line);
    Graph::draw(ui->wdg_signalCutDtfRe, signalDtfRe, Graph::Bar);
    Graph::draw(ui->wdg_signalCutDtfIm, signalDtfIm, Graph::Bar);
    Graph::draw(ui->wdg_signalCutDtfAbs, signalDtfAbs, Graph::Bar);
}


void MainWindow::on_pshBtn_signalNoiseReset_clicked()
{
    ui->lnEdit_signalNoiseDev->setText("10");
}

void MainWindow::on_pshBtn_signalNoiseLoad_clicked()
{
    double d = ui->lnEdit_signalNoiseDev->text().toDouble();
    QVector<double> noise = Signal::createGaussianNoise(_signal.size(), d);

    _signalNoise = Transform::combine(_signal, noise);

    QVector<ComplexNum> signalDtf = Transform::DTF(_signalNoise);
    QVector<double> signalDtfRe = toRe(signalDtf);
    QVector<double> signalDtfIm = toIm(signalDtf);
    QVector<double> signalDtfAbs = toAbs(signalDtf);

    if (ui->chkBox_signalNoiseDtfAbs->isChecked()) {
        signalDtfAbs.resize(signalDtfAbs.size() / 2);
    }

    Graph::draw(ui->wdg_signalNoise, _signalNoise, Graph::Line);
    Graph::draw(ui->wdg_signalNoiseDtfRe, signalDtfRe, Graph::Bar);
    Graph::draw(ui->wdg_signalNoiseDtfIm, signalDtfIm, Graph::Bar);
    Graph::draw(ui->wdg_signalNoiseDtfAbs, signalDtfAbs, Graph::Bar);
}

void MainWindow::on_pshBtn_signalBlurReset_clicked()
{
    ui->lnEdit_signalBlurD->setText("10");
    ui->lnEdit_signalBlurN->setText("10");
}

void MainWindow::on_pshBtn_signalBlurLoad_clicked()
{
    bool extrVal = ui->chkBox_signalBlurExtrVal->isChecked();
    int n = ui->lnEdit_signalBlurN->text().toInt();
    double d = ui->lnEdit_signalBlurD->text().toDouble();

    QVector<double> signalBlur = Transform::blur(_signalNoise, n, d, extrVal);
    QVector<ComplexNum> signalDtf = Transform::DTF(signalBlur);
    QVector<double> signalDtfRe = toRe(signalDtf);
    QVector<double> signalDtfIm = toIm(signalDtf);
    QVector<double> signalDtfAbs = toAbs(signalDtf);

    if (ui->chkBox_signalBlurDtfAbs->isChecked()) {
        signalDtfAbs.resize(signalDtfAbs.size() / 2);
    }

    Graph::draw(ui->wdg_signalBlur, signalBlur, Graph::Line);
    Graph::draw(ui->wdg_gauss, Signal::createGaussian(d, n), Graph::Bar);
    Graph::draw(ui->wdg_signalBlurDtfRe, signalDtfRe, Graph::Bar);
    Graph::draw(ui->wdg_signalBlurDtfIm, signalDtfIm, Graph::Bar);
    Graph::draw(ui->wdg_signalBlurDtfAbs, signalDtfAbs, Graph::Bar);
}

void MainWindow::_setDefaultSettings()
{
    on_pshBtn_signalReset_clicked();
    on_pshBtn_signalCutReset_clicked();
    on_pshBtn_signalNoiseReset_clicked();
    on_pshBtn_signalBlurReset_clicked();
}


void MainWindow::on_pshBtn_signalAllSave_clicked()
{
    ui->wdg_signal->savePng("signal.png");
    ui->wdg_signalDtfRe->savePng("signalDtfRe.png");
    ui->wdg_signalDtfIm->savePng("signalDtfIm.png");
    ui->wdg_signalDtfAbs->savePng("signalDtfAbs.png");
}

void MainWindow::on_pshBtn_signalCutAllSave_clicked()
{
    ui->wdg_signalCut->savePng("signalCut.png");
    ui->wdg_signalCutDtfRe->savePng("signalCutDtfRe.png");
    ui->wdg_signalCutDtfIm->savePng("signalCutDtfIm.png");
    ui->wdg_signalCutDtfAbs->savePng("signalCutDtfAbs.png");
}

void MainWindow::on_pshBtn_signalNoiseAllSave_clicked()
{
    ui->wdg_signalNoise->savePng("signalNoise.png");
    ui->wdg_signalNoiseDtfRe->savePng("signalNoiseDtfRe.png");
    ui->wdg_signalNoiseDtfIm->savePng("signalNoiseDtfIm.png");
    ui->wdg_signalNoiseDtfAbs->savePng("signalNoiseDtfAbs.png");
}

void MainWindow::on_pshBtn_signalBlurAllSave_clicked()
{
    ui->wdg_signalBlur->savePng("signalBlur.png");
    ui->wdg_gauss->savePng("gauss.png");
    ui->wdg_signalBlurDtfRe->savePng("signalBlurDtfRe.png");
    ui->wdg_signalBlurDtfIm->savePng("signalBlurDtfIm.png");
    ui->wdg_signalBlurDtfAbs->savePng("signalBlurDtfAbs.png");
}


