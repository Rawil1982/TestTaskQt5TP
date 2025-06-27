QT += core gui widgets sql
CONFIG += c++17

TARGET = rawil_gui
TEMPLATE = lib

DEFINES += RAWIL_GUI_LIBRARY

SOURCES += \
    presentation/viewmodels/countersviewmodel.cpp \
    presentation/views/mainwindow.cpp \
    presentation/models/counterstablemodel.cpp

HEADERS += \
    presentation/viewmodels/countersviewmodel.h \
    presentation/views/mainwindow.h \
    presentation/models/counterstablemodel.h

INCLUDEPATH += . ../rawil_core

LIBS += -L$$OUT_PWD/../rawil_core/debug -lrawil_core
