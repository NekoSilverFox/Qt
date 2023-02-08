QT += core testlib gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES +=  tst_widgettester.cpp \
            ../App/widget.cpp

HEADERS += \
            ../App/widget.h

FORMS += \
            ../App/widget.ui
