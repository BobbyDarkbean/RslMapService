TEMPLATE = lib
CONFIG += c++11
QT = core

DESTDIR = ../bin
TARGET = RmsCore

HEADERS += \
    employee.h \
    log.h \
    request.h \
    rms_global.h \
    rmscore_module.h \
    rmscore_shared.h \
    user.h

SOURCES += \
    employee.cpp \
    log.cpp \
    request.cpp \
    rms_global.cpp \
    rmscore_module.cpp \
    user.cpp

TRANSLATIONS += \
    languages/core.en_US.ts \
    languages/core.ru_RU.ts

DEFINES += \
    RMS_CORE_LIB
