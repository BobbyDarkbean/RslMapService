TEMPLATE = lib
QT = core sql

DESTDIR = ../bin
TARGET = RmsData

HEADERS += \
    queryloader.h \
    rmsdata_shared.h

SOURCES += \
    queryloader.cpp

DEFINES += \
    RMS_DATA_LIB
