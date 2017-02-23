#pragma once
#include <QMainWindow>

#include "qcustomplot_lib/qcustomplot.h" //QCustomPlot
#include "ui_mainwindow.h"
#include "graph.h"

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
};

