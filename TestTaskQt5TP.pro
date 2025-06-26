QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/countermanager.cpp \
    src/countersmodel.cpp \
    src/databasefactory.cpp \
    src/databaseworker.cpp \
    src/incrementworker.cpp \
    src/mainwindow.cpp \
    src/sqlitedatabase.cpp \
    src/sqlitedatabaseinitializer.cpp \
    src/simpleincrementstrategy.cpp \
    src/workermanager.cpp \
    src/commands/addcommand.cpp \
    src/commands/removecommand.cpp \
    src/commands/savecommand.cpp

HEADERS += \
    headers/countermanager.h \
    headers/countersmodel.h \
    headers/databasefactory.h \
    headers/databaseworker.h \
    headers/incrementworker.h \
    headers/mainwindow.h \
    headers/simpleincrementstrategy.h \
    headers/sqlitedatabase.h \
    headers/sqlitedatabaseinitializer.h \
    headers/workermanager.h \
    headers/interfaces/idatabase.h \
    headers/interfaces/idatabaseinitializer.h \
    headers/interfaces/iincrementstrategy.h \
    headers/interfaces/iworker.h \
    headers/interfaces/iworkermanager.h \
    headers/commands/icommand.h \
    headers/commands/addcommand.h \
    headers/commands/removecommand.h \
    headers/commands/savecommand.h

FORMS += \
    uis/mainwindow.ui

TRANSLATIONS += \
    TestTaskQt5TP_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
