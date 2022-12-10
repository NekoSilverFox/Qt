#-------------------------------------------------
#
# Project created by QtCreator 2022-01-14T14:01:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTcpFile
TEMPLATE = app


SOURCES += main.cpp\
        tcpserverwidget.cpp \
    tcpclientwidget.cpp

HEADERS  += tcpserverwidget.h \
    tcpclientwidget.h

FORMS    += tcpserverwidget.ui \
    tcpclientwidget.ui

CONFIG += C++11
