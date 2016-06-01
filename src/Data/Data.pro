TEMPLATE = lib
CONFIG += c++11
QT = core sql

DESTDIR = ../bin
TARGET = RmsData

INCLUDEPATH += \
    ../Core

LIBS += -L../bin -lRmsCore

include(dataadapters/DataAdapters.pri)

HEADERS += \
    datastorageconfigurator.h \
    queryloader.h \
    rmsdata_shared.h

SOURCES += \
    datastorageconfigurator.cpp \
    queryloader.cpp

RESOURCES += \
    resources.qrc

DEFINES += \
    RMS_DATA_LIB
