TEMPLATE = lib
CONFIG += c++11
QT = core gui widgets

DESTDIR = ../bin
TARGET = RmsGui

INCLUDEPATH += \
    ../Core \
    ../Logic

LIBS += -L../bin -lRmsCore -lRmsLogic

include(itemdelegates/ItemDelegates.pri)

HEADERS += \
    rmsgui_shared.h

DEFINES += \
    RMS_GUI_LIB
