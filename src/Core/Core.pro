TEMPLATE = lib
QT = core

TARGET = RmsCore

HEADERS += \
    rms_global.h \
    rms_shared.h \
    user.h

SOURCES += \
    rms_global.cpp \
    user.cpp

DEFINES += \
    RMS_CORE_LIB
