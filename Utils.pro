#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T09:57:37
#
#-------------------------------------------------

QT       += core gui network webkitwidgets
QT       += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Utils
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    editorwindows.cpp

HEADERS  += mainwindow.h \
    parserconfig.hpp \
    config.h \
    editorwindows.h

FORMS    += mainwindow.ui \
    editorwindows.ui
