#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T09:57:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Utils
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    parserconfig.hpp \
    config.h

FORMS    += mainwindow.ui
