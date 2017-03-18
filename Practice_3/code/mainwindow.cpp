#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_lib/complexnum.h"
#include "graph.h"
#include "functions.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Graph signal(ui->wdg_signal);
    signal.setDrawType(Graph::Line);
    Graph re(ui->wdg_re);
    re.setDrawType(Graph::Bar);
    Graph im(ui->wdg_im);
    im.setDrawType(Graph::Bar);
    Graph abs(ui->wdg_abs);
    abs.setDrawType(Graph::Bar);
    Graph compare(ui->wdg_compare);
    compare.setDrawType(Graph::Bar);

    _graps.insert(Signal, signal);
    _graps.insert(Re, re);
    _graps.insert(Im, im);
    _graps.insert(Abs, abs);
    _graps.insert(Compare, compare);

    on_btn_signalReset_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_reExpand_toggled(bool checked)
{
    if (checked) {
        ui->btn_imExpand->setChecked(false);
        ui->btn_absExpand->setChecked(false);
    }

    ui->hLayout_Complex->setStretch(0, (checked) ? 1 : 0);
    ui->hLayout_Complex->setStretch(1, 0);
    ui->hLayout_Complex->setStretch(2, 0);
}

void MainWindow::on_btn_imExpand_toggled(bool checked)
{
    if (checked) {
        ui->btn_reExpand->setChecked(false);
        ui->btn_absExpand->setChecked(false);
    }

    ui->hLayout_Complex->setStretch(0, 0);
    ui->hLayout_Complex->setStretch(1, (checked) ? 1 : 0);
    ui->hLayout_Complex->setStretch(2, 0);
}

void MainWindow::on_btn_absExpand_toggled(bool checked)
{
    if (checked) {
        ui->btn_reExpand->setChecked(false);
        ui->btn_imExpand->setChecked(false);
    }

    ui->hLayout_Complex->setStretch(0, 0);
    ui->hLayout_Complex->setStretch(1, 0);
    ui->hLayout_Complex->setStretch(2, (checked) ? 1 : 0);
}

void MainWindow::on_btn_signalReset_clicked()
{
    ui->spBx_signalStep->setValue(0.1);
    ui->spBx_signalCount->setValue(1000);
    ui->spBx_signalAlfa->setValue(500);
    ui->spBx_signalBeta->setValue(1);
    ui->spBx_signalSigma->setValue(10);
    ui->spBx_signalMu->setValue(50);
    ui->spBx_noiseSet->setValue(0.5);
    ui->spBx_filterSet->setValue(4);
}

void MainWindow::on_btn_signalLoad_clicked()
{
    // SIGNAL PLOTTING
    int count    = ui->spBx_signalCount->value();
    double step  = ui->spBx_signalStep->value();
    double alfa  = ui->spBx_signalAlfa->value();
    double beta  = ui->spBx_signalBeta->value();
    double sigma = ui->spBx_signalSigma->value();
    double mu    = ui->spBx_signalMu->value();

    _originalSignal = Functions::createSignal(alfa, beta, mu, sigma, step, count);

    if (ui->chBx_filter->isChecked()) {
        double f = ui->spBx_filterSet->value();
        _originalSignal = Functions::filtration(_originalSignal, f);
    }
    if (ui->chBx_noise->isChecked()) {
        double d = ui->spBx_noiseSet->value();
        _originalSignal = Functions::addGaussianNoise(_originalSignal, d);
    }

    _graps[Signal].setPoints(_originalSignal);
    _graps[Signal].draw();

    //DTF PLOTTING
    QVector<ComplexNum> complex = Functions::DTF(_originalSignal);
    _graps[Re].setPoints(toRe(complex));
    _graps[Re].draw();
    _graps[Im].setPoints(toIm(complex));
    _graps[Im].draw();
    _graps[Abs].setPoints(toAbs(complex));
    _graps[Abs].draw();

    //SET FREQUENCY
    QVector<double> abs = _graps[Abs].getPoints();
    double f;
    const double eps = ui->spBx_frequencyMin->value();

    const double n = abs.size();
    for (int i = 0; i < n / 2; i++) {
        f = i;
        if (abs[i] < eps) break;
    }
    ui->lnEd_freq->setText(QString::number(f));
}

void MainWindow::on_spBx_signalCount_editingFinished()
{
    int count = ui->spBx_signalCount->value();
    ui->spBx_signalStep->setValue(100.0 / count);
}

void MainWindow::on_spBx_signalStep_editingFinished()
{
    double step = ui->spBx_signalStep->value();
    ui->spBx_signalCount->setValue(100.0 / step);
}

void MainWindow::on_btn_reHalf_toggled(bool checked)
{
    _graps[Re].showHalf(checked);
}

void MainWindow::on_btn_imHalf_toggled(bool checked)
{
    _graps[Im].showHalf(checked);
}

void MainWindow::on_btn_absHalf_toggled(bool checked)
{
    _graps[Abs].showHalf(checked);
}

void MainWindow::on_btn_reAdd_clicked()
{
    _graps[Compare].setSecond(_graps[Re].getPoints());
}

void MainWindow::on_btn_imAdd_clicked()
{
    _graps[Compare].setSecond(_graps[Im].getPoints());
}

void MainWindow::on_btn_absAdd_clicked()
{
    _graps[Compare].setSecond(_graps[Abs].getPoints());
}

void MainWindow::on_btn_compareClear_clicked()
{
    _graps[Compare].clear();
}

void MainWindow::on_btn_compareExpand_toggled(bool checked)
{
    ui->globalLayout->setStretch(4, (checked) ? 1 : 0);
}

void MainWindow::on_btn_compareHalf_toggled(bool checked)
{
    _graps[Compare].showHalf(checked);
}

void MainWindow::on_btn_signalAdd_clicked()
{
    _graps[Compare].setSecond(_graps[Signal].getPoints());
}

void MainWindow::on_btn_savePic_clicked()
{
    _graps[Signal].savePng("Signal");
    _graps[Re].savePng("Re");
    _graps[Im].savePng("Im");
    _graps[Abs].savePng("Abs");
    _graps[Compare].savePng("Compare");
}

void MainWindow::on_btn_compareShowForFm_toggled(bool checked)
{
    int n = checked ?
                ui->lnEd_compareShowFrom->text().toInt()
                : _graps[Compare].getPoints().size();

    _graps[Compare].showCount(n);
}
