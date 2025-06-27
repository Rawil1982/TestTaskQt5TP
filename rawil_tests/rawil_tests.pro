QT += core gui widgets sql testlib
CONFIG += c++17 console

TARGET = rawil_tests
TEMPLATE = app

INCLUDEPATH += ../rawil_core ../rawil_gui

LIBS += -L$$OUT_PWD/../rawil_core/debug -lrawil_core
LIBS += -L$$OUT_PWD/../rawil_gui/debug -lrawil_gui

SOURCES += \
    main.cpp
