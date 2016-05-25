TEMPLATE = lib
CONFIG += c++11
QT = core sql

DESTDIR = ../bin
TARGET = RmsData

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
