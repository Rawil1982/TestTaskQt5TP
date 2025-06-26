#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include "headers/interfaces/idatabase.h"
#include <memory>

class DatabaseFactory {
public:
    static std::unique_ptr<IDatabase> createDatabase();
};

#endif // DATABASEFACTORY_H
