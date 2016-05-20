TEMPLATE = lib
QT = core

TARGET = RmsCore

HEADERS += \
    request.h \
    rms_global.h \
    rmscore_shared.h \
    user.h

SOURCES += \
    request.cpp \
    rms_global.cpp \
    user.cpp

DEFINES += \
    RMS_CORE_LIB
