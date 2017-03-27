#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_lib/complexnum.h"

#include "my_lib/functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _graph = Graph(ui->wdg_graph);
    _calculate = Graph(ui->wdg_calculate);
    _calculate.setDrawType(Graph::Line);

    on_btn_signalReset_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chBx_noise_toggled(bool checked)
{
        ui->spBx_noiseFrom->setEnabled(checked);
        ui->spBx_noiseTo->setEnabled(checked);
        ui->spBx_noiseCount->setValue(ui->spBx_signalCount->value());
        ui->spBx_noisesNumber->setValue(1);
}

void MainWindow::on_grBox_signalSettings_clicked()
{
    bool checked = ui->grBox_signalSettings->isChecked();

    ui->chBx_noise->setChecked(checked &&  ui->chBx_noise->isChecked());

    ui->grBox_signalSettings->setChecked(checked);
    ui->grBox_noiseSettings->setChecked(!checked);

    ui->rBtn_cov->setEnabled(checked);
    ui->rBtn_spectOfCov->setEnabled(checked);
}

void MainWindow::on_grBox_noiseSettings_clicked()
{
       bool checked = ui->grBox_noiseSettings->isChecked();
        ui->grBox_signalSettings->setChecked(!checked);
        ui->grBox_noiseSettings->setChecked(checked);

        ui->spBx_noiseFrom->setEnabled(true);
        ui->spBx_noiseTo->setEnabled(true);

        ui->rBtn_cov->setEnabled(!checked);
        ui->rBtn_spectOfCov->setEnabled(!checked);

}

void MainWindow::on_btn_build_clicked()
{
    QVector<double> mainGraph;

    // SIGNAL PLOTTING
    if (ui->grBox_signalSettings->isChecked()){
        ui->stackedWidget->setCurrentIndex(0);

        int count    = ui->spBx_signalCount->value();
        double step  = ui->spBx_signalStep->value();
        double alfa  = ui->spBx_signalAlfa->value();
        double beta  = ui->spBx_signalBeta->value();
        double sigma = ui->spBx_signalSigma->value();
        double mu    = ui->spBx_signalMu->value();

        mainGraph = Functions::createSignal(alfa, beta, mu, sigma, step, count);
        if (ui->chBx_filter->isChecked()) {
            double f = ui->spBx_filterSet->value();
            mainGraph = Functions::filtration(mainGraph, f);
        }
        if (ui->chBx_noise->isChecked()) {
            double a = ui->spBx_noiseFrom->value();
            double b = ui->spBx_noiseTo->value();
            double u = ui->spBx_signalNoiseU->value();
            mainGraph = Functions::addNormalNoise(mainGraph, a, b, u);
        }

        _graph.setPoints(mainGraph);
        _graph.draw();


        if (ui->rBtn_spect->isChecked()) {
            QVector<QVector<ComplexNum> > g;
            QVector<ComplexNum> g1 = Functions::DTF(mainGraph);
            g.push_back(g1);

            QVector<double> spect = spectDensity(g);

            _calculate.setDrawType(Graph::Bar);
            _calculate.setPoints(spect);
            _calculate.draw();
        }

        if (ui->rBtn_cov->isChecked()) {
            QVector<double> cov = Functions::autocovariance(mainGraph);
//            cov = Functions::autocovariance(cov);
//            cov = Functions::autocovariance(cov);
//            cov = Functions::autocovariance(cov);
//            cov = Functions::autocovariance(cov);
//            cov = Functions::autocovariance(cov);

            _calculate.setDrawType(Graph::Line);
            _calculate.setPoints(cov);
            _calculate.draw();
        }

        if (ui->rBtn_spectOfCov->isChecked()) {

            QVector<double> cov = Functions::autocovariance(mainGraph);
            QVector<ComplexNum> complCov = Functions::DTF(cov);


            _calculate.setDrawType(Graph::Bar);
            _calculate.setPoints(toAbs(complCov));
            _calculate.draw();

        }

    }
    //=============================================================

    // NOISE PLOTTING
    if (ui->grBox_noiseSettings->isChecked()){
        ui->stackedWidget->setCurrentIndex(1);

        delete ui->wdg_noises->layout();

        QTabWidget *tabs = new QTabWidget();
        QVBoxLayout* layout = new QVBoxLayout(ui->wdg_noises);
        layout->addWidget(tabs);

        int count = ui->spBx_noiseCount->value();
        double from = ui->spBx_noiseFrom->value();
        double to = ui->spBx_noiseTo->value();
        int number = ui->spBx_noisesNumber->value();

        QVector<QVector<ComplexNum> > noisesComplex;

        for (int i = 0; i < number; ++i) {
            QVector<double> noise = Functions::createNormalNoise(count, from, to);
            QWidget *area = new QWidget();
            tabs->addTab(area, QString::number(i));

            Graph tmpGraph(area);
            tmpGraph.setPoints(noise);
            tmpGraph.draw();

            noisesComplex.push_back(Functions::DTF(noise));
        }
        //CALCULATE PLOTTING

        if (ui->rBtn_spect->isChecked()) {
            QVector<double> spect = spectDensity(noisesComplex);

            _calculate.setDrawType(Graph::Bar);
            _calculate.setPoints(spect);
            _calculate.draw();
        }
    }

}

void MainWindow::on_btn_signalReset_clicked()
{
    //SIGNAL
    ui->spBx_signalStep->setValue(0.1);
    ui->spBx_signalCount->setValue(1000);
    ui->spBx_signalAlfa->setValue(500);
    ui->spBx_signalBeta->setValue(1);
    ui->spBx_signalSigma->setValue(10);
    ui->spBx_signalMu->setValue(50);
    ui->spBx_filterSet->setValue(4);
    ui->chBx_filter->setChecked(false);
    ui->chBx_noise->setChecked(false);

    //NOISE
    ui->spBx_noiseCount->setValue(1000);
    ui->spBx_noiseFrom->setValue(-0.5);
    ui->spBx_noiseTo->setValue(0.5);
    ui->spBx_noisesNumber->setValue(5);

    //
    ui->rBtn_spect->setChecked(true);


}
