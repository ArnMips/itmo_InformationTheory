#pragma once
#include <QMainWindow>
#include "qcustomplot_lib/qcustomplot.h"

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

