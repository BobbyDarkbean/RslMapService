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
include(requeststates/RequestStates.pri)

HEADERS += \
    datamodelfacade.h \
    defaultsignaltrigger.h \
    requeststate.h \
    requeststatemachine.h \
    rmslogic_module.h \
    rmslogic_shared.h \
    signaltrigger.h \
    workflow.h

SOURCES += \
    datamodelfacade.cpp \
    defaultsignaltrigger.cpp \
    requeststate.cpp \
    requeststatemachine.cpp \
    rmslogic_module.cpp \
    signaltrigger.cpp \
    workflow.cpp

TRANSLATIONS += \
    languages/logic.en_US.ts \
    languages/logic.ru_RU.ts

DEFINES += \
    RMS_LOGIC_LIB
