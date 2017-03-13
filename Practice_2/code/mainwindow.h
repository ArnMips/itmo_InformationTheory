#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QMap>
#include "signal.h"
#include "graph.h"
#include "transforms.h"
#include "complexnum.h"

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
    void on_pshBtn_signalLoad_clicked();
    void on_pshBtn_signalCutLoad_clicked();
    void on_pshBtn_signalNoiseLoad_clicked();
    void on_pshBtn_signalBlurLoad_clicked();

    void on_pshBtn_signalCutReset_clicked();
    void on_pshBtn_signalReset_clicked();
    void on_pshBtn_signalNoiseReset_clicked();
    void on_pshBtn_signalBlurReset_clicked();

    void on_pshBtn_signalAllSave_clicked();
    void on_pshBtn_signalCutAllSave_clicked();
    void on_pshBtn_signalNoiseAllSave_clicked();
    void on_pshBtn_signalBlurAllSave_clicked();

private:
    void _setDefaultSettings();
    Ui::MainWindow *ui;
    QVector<double> _signal;
    QVector<double> _signalNoise;
};

#endif // MAINWINDOW_H
