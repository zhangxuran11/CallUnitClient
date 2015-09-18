#-------------------------------------------------
#
# Project created by QtCreator 2015-07-17T18:50:17
#
#-------------------------------------------------

QT       += core gui network

TARGET = CallUnitClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    network.cpp \
    callctlunit.cpp

HEADERS  += mainwindow.h \
    parser.h \
    network.h \
    config.h \
    callctlunit.h

FORMS    += mainwindow.ui
