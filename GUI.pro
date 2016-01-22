#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T22:33:22
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    server.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
