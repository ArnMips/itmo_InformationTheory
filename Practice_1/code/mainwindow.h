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
    void on_pushBtn_signalLoad_clicked();
    void on_pushBtn_signaReset_clicked();
    void on_pushBtn_signalHistReset_clicked();
    void on_pushBtn_signalHistLoad_clicked();

private:
    Ui::MainWindow *ui;
    SignalProcessor _signalProc;

    QVector<double> _signal;
    QVector<double> _signalHist;
    QVector<double> _noise;
    QVector<double> _noiseHist;
    QVector<double> _convolution;
    QVector<double> _combSingnals;
    QVector<double> _combSingnalsHist;

    void _mainFunction();
    QVector<double> _fillAray(const double minV, const double maxV, const double step);
};

