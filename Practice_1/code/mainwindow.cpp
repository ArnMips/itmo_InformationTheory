#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ///=========Testing graphics  ================================
    QVector<double> x, y;

    for (int i = 0; i < 1000; i++) {
        y.push_back(rand() % 100);
        x.push_back(i);
    }

    Graph graphPainter;

    graphPainter.drawLineGraph(ui->widget, x,y);
    graphPainter.drawBarGraph(ui->widget_2, x,y);


    ///===========================================================
}

MainWindow::~MainWindow()
{
    delete ui;
}

