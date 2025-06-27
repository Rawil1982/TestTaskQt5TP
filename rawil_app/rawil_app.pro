QT += core gui widgets sql
CONFIG += c++17

TARGET = rawil_app
TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += ../rawil_core ../rawil_gui

LIBS += -L$$OUT_PWD/../rawil_core/debug -lrawil_core
LIBS += -L$$OUT_PWD/../rawil_gui/debug -lrawil_gui
