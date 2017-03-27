QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Practice_4
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
    	qcustomplot_lib/qcustomplot.cpp \
    	my_lib/complexnum.cpp \
        my_lib/functions.cpp \
        my_lib/graph.cpp \

HEADERS  += mainwindow.h \
    	qcustomplot_lib/qcustomplot.h \
    	my_lib/complexnum.h \
        my_lib/functions.h \
        my_lib/graph.h \

FORMS    += mainwindow.ui
