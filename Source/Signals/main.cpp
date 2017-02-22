#include "ui_Form.h"
#include "graphics.h"
#include "signalscreator.h"

#include <QtWidgets>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QWidget* form = new QWidget;
    Ui::MyForm ui;
    ui.setupUi(form);

    SignalsCreator signalCreator;

//-----------------------------------------------------------------------------

    QList<qreal> pntsOfNoise = signalCreator.getGaussianNoise(-14.6, 19.9, 1000);
    QList<QPointF> tablePntsOfNoise;
    for (int i(0); i < pntsOfNoise.size(); ++i) {
        tablePntsOfNoise.push_back(QPointF(i, pntsOfNoise.at(i)));
    }

    QList<QPointF> tablePntsHistOfNoise = signalCreator.createHistogram(tablePntsOfNoise, 0.1);

    QList<qreal> pntsOfSignal = signalCreator.getSpecialSignal(1000);
    QList<QPointF> tablePntsOfSignal;
    for (int i(0); i < pntsOfSignal.size(); ++i) {
        tablePntsOfSignal.push_back(QPointF(i, pntsOfSignal.at(i)));
    }
    QList<QPointF> tablePntsHistOfSignal = signalCreator.createHistogram(tablePntsOfSignal, 0.1);

    QList<QPointF> combinedSignal = signalCreator.combineSignals(tablePntsOfSignal, tablePntsOfNoise);
    QList<QPointF> combinedSignalHist = signalCreator.createHistogram(combinedSignal, 0.1);

    Graphics graphOfSignal          (tablePntsOfSignal, ui.widget);
    Graphics graphOfHistogramSignal (tablePntsHistOfSignal, ui.widget_2);
    Graphics graphOfNoise           (tablePntsOfNoise, ui.widget_3);
    Graphics graphOfHistogramNoise  (tablePntsHistOfNoise, ui.widget_4);
    Graphics graphOfcombinedSignal  (combinedSignal, ui.widget_5);
    Graphics graphOfHistcombinedSignal(combinedSignalHist, ui.widget_6);

//-----------------------------------------------------------------------------

    form->resize(app.desktop()->width(), form->height());
    form->show();

    return app.exec();
}
