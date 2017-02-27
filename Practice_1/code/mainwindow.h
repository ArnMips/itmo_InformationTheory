#pragma once
#include <QMainWindow>
#include "qcustomplot_lib/qcustomplot.h" //QCustomPlot
#include "ui_mainwindow.h"
#include "graph.h"
#include "signal_processor.h"

//=============================================================================
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_signalLoad_clicked();
    void on_btn_signalReset_clicked();
    void on_btn_signalHistReset_clicked();
    void on_btn_signalHistLoad_clicked();
    void on_btn_hoiseReset_clicked();
    void on_btn_noiseLoad_clicked();
    void on_btn_noiseHistLoat_clicked();
    void on_btn_noiseHistReset_clicked();
    void on_btn_signalNoiseLoad_clicked();

private:
    Ui::MainWindow *ui;
    SignalProcessor _signalProc;

    QVector<double> _signal;
    QVector<double> _signalHist;
    QVector<double> _noise;
    QVector<double> _noiseHist;

    QVector<double> _fillAray(const double minV, const double maxV, const double step);

    void _help();
};

