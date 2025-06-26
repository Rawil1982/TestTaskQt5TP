#include "headers/databasefactory.h"
#include "headers/sqlitedatabase.h"

std::unique_ptr<IDatabase> DatabaseFactory::createDatabase() {
    return std::make_unique<SQLiteDatabase>("counters.db");
}
