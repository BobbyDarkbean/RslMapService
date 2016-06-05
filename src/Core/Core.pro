TEMPLATE = lib
CONFIG += c++11
QT = core

DESTDIR = ../bin
TARGET = RmsCore

HEADERS += \
    employee.h \
    request.h \
    rms_global.h \
    rmscore_module.h \
    rmscore_shared.h \
    user.h

SOURCES += \
    employee.cpp \
    request.cpp \
    rms_global.cpp \
    rmscore_module.cpp \
    user.cpp

DEFINES += \
    RMS_CORE_LIB
