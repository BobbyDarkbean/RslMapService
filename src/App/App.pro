TEMPLATE = app
CONFIG += c++11
QT = core gui widgets

DESTDIR = ../bin
TARGET = RmsApp

INCLUDEPATH += \
    ../Core \
    ../Logic \
    ../Gui

LIBS += -L../bin -lRmsCore -lRmsLogic -lRmsGui

HEADERS += \
    application.h \
    mainwindow.h \
    rmsapp_module.h

SOURCES += \
    application.cpp \
    main.cpp \
    mainwindow.cpp \
    rmsapp_module.cpp

TRANSLATIONS += \
    languages/app.en_US.ts \
    languages/app.ru_RU.ts
