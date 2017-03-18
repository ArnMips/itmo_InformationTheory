#pragma once
#include <QMainWindow>
#include <QMap>
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

private slots:
    void on_btn_reExpand_toggled(bool checked);
    void on_btn_imExpand_toggled(bool checked);
    void on_btn_absExpand_toggled(bool checked);
    void on_btn_signalReset_clicked();
    void on_btn_signalLoad_clicked();
    void on_spBx_signalCount_editingFinished();
    void on_spBx_signalStep_editingFinished();
    void on_btn_reHalf_toggled(bool checked);
    void on_btn_imHalf_toggled(bool checked);
    void on_btn_absHalf_toggled(bool checked);
    void on_btn_reAdd_clicked();
    void on_btn_imAdd_clicked();
    void on_btn_absAdd_clicked();
    void on_btn_compareClear_clicked();
    void on_btn_compareExpand_toggled(bool checked);
    void on_btn_compareHalf_toggled(bool checked);

    void on_btn_signalAdd_clicked();

    void on_btn_savePic_clicked();

    void on_btn_compareShowForFm_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    enum graphType { Signal, Re, Im, Abs, Compare };
    QMap<graphType, Graph> _graps;
    QVector<double> _originalSignal;
};

