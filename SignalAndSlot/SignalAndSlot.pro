#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T20:24:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SignalAndSlot
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mysubwidget.cpp \
    mybutton.cpp

HEADERS  += mywidget.h \
    mysubwidget.h \
    mybutton.h

CONFIG += C++11
