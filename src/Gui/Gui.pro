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
include(widgets/Widgets.pri)

HEADERS += \
    rmsgui_module.h \
    rmsgui_shared.h

SOURCES += \
    rmsgui_module.cpp

DEFINES += \
    RMS_GUI_LIB
