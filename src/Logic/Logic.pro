TEMPLATE = lib
CONFIG += c++11
QT = core sql

DESTDIR = ../bin
TARGET = RmsLogic

INCLUDEPATH += \
    ../Data

LIBS += -L../bin -lRmsCore -lRmsData

HEADERS += \
    rmslogic_shared.h \
    workflow.h

SOURCES += \
    workflow.cpp

DEFINES += \
    RMS_LOGIC_LIB
