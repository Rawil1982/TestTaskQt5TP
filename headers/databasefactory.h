#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include "idatabase.h"
#include <memory>

class DatabaseFactory {
public:
    static std::unique_ptr<IDatabase> createDatabase();
};

#endif // DATABASEFACTORY_H
