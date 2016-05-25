TEMPLATE = app
CONFIG += c++11
QT = core gui widgets

DESTDIR = ../bin
TARGET = RmsApp

INCLUDEPATH += \
    ../Logic

LIBS += -L../bin -lRmsLogic

HEADERS += \
    application.h

SOURCES += \
    application.cpp \
    main.cpp
