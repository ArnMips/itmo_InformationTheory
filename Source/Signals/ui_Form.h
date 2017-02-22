/********************************************************************************
** Form generated from reading UI file 'FormHp9420.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FORMHP9420_H
#define FORMHP9420_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tb1Signal;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QWidget *widget;
    QWidget *tb2Noise;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *widget_3;
    QWidget *widget_4;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *tb3Convolution;
    QVBoxLayout *verticalLayout;
    QLabel *label_10;
    QWidget *widget_7;
    QWidget *tb4SignalNoise;
    QGridLayout *gridLayout_4;
    QLabel *label_9;
    QWidget *widget_5;
    QLabel *label_8;
    QWidget *widget_6;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QStringLiteral("MyForm"));
        MyForm->resize(891, 400);
        MyForm->setCursor(QCursor(Qt::ArrowCursor));
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(MyForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tb1Signal = new QWidget();
        tb1Signal->setObjectName(QStringLiteral("tb1Signal"));
        gridLayout_2 = new QGridLayout(tb1Signal);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit = new QLineEdit(tb1Signal);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 1, 2, 1, 1);

        label_3 = new QLabel(tb1Signal);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        label_2 = new QLabel(tb1Signal);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        label = new QLabel(tb1Signal);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 2, 1, 1);

        widget_2 = new QWidget(tb1Signal);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        gridLayout_2->addWidget(widget_2, 1, 1, 2, 1);

        widget = new QWidget(tb1Signal);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout_2->addWidget(widget, 1, 0, 2, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        tabWidget->addTab(tb1Signal, QString());
        tb2Noise = new QWidget();
        tb2Noise->setObjectName(QStringLiteral("tb2Noise"));
        gridLayout_3 = new QGridLayout(tb2Noise);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(tb2Noise);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(tb2Noise);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(tb2Noise);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 0, 2, 1, 1);

        widget_3 = new QWidget(tb2Noise);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        gridLayout_3->addWidget(widget_3, 1, 0, 2, 1);

        widget_4 = new QWidget(tb2Noise);
        widget_4->setObjectName(QStringLiteral("widget_4"));

        gridLayout_3->addWidget(widget_4, 1, 1, 2, 1);

        lineEdit_2 = new QLineEdit(tb2Noise);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_3->addWidget(lineEdit_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 2, 2, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        tabWidget->addTab(tb2Noise, QString());
        tb3Convolution = new QWidget();
        tb3Convolution->setObjectName(QStringLiteral("tb3Convolution"));
        verticalLayout = new QVBoxLayout(tb3Convolution);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_10 = new QLabel(tb3Convolution);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);

        widget_7 = new QWidget(tb3Convolution);
        widget_7->setObjectName(QStringLiteral("widget_7"));

        verticalLayout->addWidget(widget_7);

        verticalLayout->setStretch(1, 1);
        tabWidget->addTab(tb3Convolution, QString());
        tb4SignalNoise = new QWidget();
        tb4SignalNoise->setObjectName(QStringLiteral("tb4SignalNoise"));
        gridLayout_4 = new QGridLayout(tb4SignalNoise);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_9 = new QLabel(tb4SignalNoise);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 0, 2, 1, 1);

        widget_5 = new QWidget(tb4SignalNoise);
        widget_5->setObjectName(QStringLiteral("widget_5"));

        gridLayout_4->addWidget(widget_5, 1, 0, 2, 1);

        label_8 = new QLabel(tb4SignalNoise);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 0, 1, 1, 1);

        widget_6 = new QWidget(tb4SignalNoise);
        widget_6->setObjectName(QStringLiteral("widget_6"));

        gridLayout_4->addWidget(widget_6, 1, 1, 2, 1);

        label_7 = new QLabel(tb4SignalNoise);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(tb4SignalNoise);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_4->addWidget(lineEdit_3, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 349, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 2, 2, 1, 1);

        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 1);
        tabWidget->addTab(tb4SignalNoise, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(MyForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QApplication::translate("MyForm", "Graph", 0));
        label_3->setText(QApplication::translate("MyForm", "Entropy value", 0));
        label_2->setText(QApplication::translate("MyForm", "Distribution histogram ", 0));
        label->setText(QApplication::translate("MyForm", "Signal graph", 0));
        tabWidget->setTabText(tabWidget->indexOf(tb1Signal), QApplication::translate("MyForm", "Signal", 0));
        label_4->setText(QApplication::translate("MyForm", "Gaussian noise graph", 0));
        label_5->setText(QApplication::translate("MyForm", "Distribution histogram ", 0));
        label_6->setText(QApplication::translate("MyForm", "Entropy value", 0));
        tabWidget->setTabText(tabWidget->indexOf(tb2Noise), QApplication::translate("MyForm", "Gaussian noise", 0));
        label_10->setText(QApplication::translate("MyForm", "Convolution", 0));
        tabWidget->setTabText(tabWidget->indexOf(tb3Convolution), QApplication::translate("MyForm", "Convolution", 0));
        label_9->setText(QApplication::translate("MyForm", "Entropy value", 0));
        label_8->setText(QApplication::translate("MyForm", "Distribution histogram ", 0));
        label_7->setText(QApplication::translate("MyForm", "Signal + noise graph", 0));
        tabWidget->setTabText(tabWidget->indexOf(tb4SignalNoise), QApplication::translate("MyForm", "Signal + noise", 0));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FORMHP9420_H
