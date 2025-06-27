QT += core sql
CONFIG += c++17 moc

TARGET = rawil_core
TEMPLATE = lib

DEFINES += RAWIL_CORE_LIBRARY

SOURCES += \
    domain/entities/counter.cpp \
    domain/repositories/counterrepository.cpp \
    domain/services/frequencycalculator.cpp \
    domain/services/counterservice.cpp \
    application/commands/addcountercommand.cpp \
    application/strategies/simpleincrementstrategy.cpp \
    infrastructure/database/sqlitedatabase.cpp \
    infrastructure/workers/incrementworker.cpp

HEADERS += \
    domain/entities/counter.h \
    domain/repositories/icounterrepository.h \
    domain/repositories/counterrepository.h \
    domain/services/counterservice.h \
    domain/services/ifrequencycalculator.h \
    domain/services/frequencycalculator.h \
    application/commands/icommand.h \
    application/commands/addcountercommand.h \
    application/strategies/iincrementstrategy.h \
    application/strategies/simpleincrementstrategy.h \
    infrastructure/database/idatabase.h \
    infrastructure/database/sqlitedatabase.h \
    infrastructure/workers/incrementworker.h

INCLUDEPATH += . 