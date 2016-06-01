TEMPLATE = app
CONFIG += c++11
QT = core gui widgets

DESTDIR = ../bin
TARGET = RmsApp

INCLUDEPATH += \
    ../Logic \
    ../Gui

LIBS += -L../bin -lRmsLogic -lRmsGui

HEADERS += \
    application.h \
    mainwindow.h

SOURCES += \
    application.cpp \
    main.cpp \
    mainwindow.cpp
