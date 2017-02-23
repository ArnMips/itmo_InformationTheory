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

private:
    Ui::MainWindow *ui;
    void _mainFunction();
    QVector<double> _fillAray(const double minV, const double maxV, const double step);
};

