#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T22:33:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

CONFIG += qwt
INCLUDEPATH += /usr/local/qwt-6.1.2/include \
        /usr/local/qwt-6.1.2
LIBS += -L/usr/local/qwt-6.1.2/lib -lqwt \
    /usr/local/qwt-6.1.2/lib/libqwt.so.6
    -lqwt
DEPENDPATH += /usr/local/qwt-6.1.2/include
