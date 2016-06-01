TEMPLATE = lib
CONFIG += c++11
QT = core sql

DESTDIR = ../bin
TARGET = RmsLogic

INCLUDEPATH += \
    ../Core \
    ../Data

LIBS += -L../bin -lRmsCore -lRmsData

include(itemmodels/ItemModels.pri)

HEADERS += \
    rmslogic_shared.h \
    workflow.h

SOURCES += \
    workflow.cpp

DEFINES += \
    RMS_LOGIC_LIB
