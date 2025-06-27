#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include "headers/interfaces/idatabase.h"
#include <memory>
#include <QString>

class DatabaseFactory {
public:
    static std::unique_ptr<IDatabase> createDatabase();
private:
    static constexpr const char* m_databaseName = "counters.db";
};

#endif // DATABASEFACTORY_H
