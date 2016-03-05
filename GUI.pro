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
    server.cpp \
    cube.cpp \
    drone.cpp \
    axis.cpp \
    ground.cpp \
    target.cpp \
    move_ground.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    server.h \
    object.h \
    material.h \
    color4f.h \
    cube.h \
    drone.h \
    axis.h \
    ground.h \
    target.h \
    move_ground.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
