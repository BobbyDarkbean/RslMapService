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
    datamodelfacade.h \
    defaultsignaltrigger.h \
    rmslogic_module.h \
    rmslogic_shared.h \
    signaltrigger.h \
    workflow.h

SOURCES += \
    datamodelfacade.cpp \
    defaultsignaltrigger.cpp \
    rmslogic_module.cpp \
    signaltrigger.cpp \
    workflow.cpp

TRANSLATIONS += \
    languages/logic.en_US.ts \
    languages/logic.ru_RU.ts

DEFINES += \
    RMS_LOGIC_LIB
