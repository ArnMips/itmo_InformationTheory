#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "my_lib/graph.h"

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
    void on_chBx_noise_toggled(bool checked);
    void on_grBox_signalSettings_clicked();
    void on_grBox_noiseSettings_clicked();

    void on_btn_build_clicked();

    void on_btn_signalReset_clicked();

private:
    Ui::MainWindow *ui;

    Graph _graph;
    Graph _calculate;
};

#endif // MAINWINDOW_H
