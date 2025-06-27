#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "headers/interfaces/idatabase.h"
#include "headers/interfaces/idatabaseinitializer.h"
#include <QString>
#include <thread>
#include <memory>
#include <QSqlDatabase>

// Forward declarations
class QSqlDatabase;

class SQLiteDatabase : public IDatabase {
public:
    explicit SQLiteDatabase(QString databaseName, 
                           std::unique_ptr<IDatabaseInitializer> initializer = nullptr);

    // IDatabase interface
    ~SQLiteDatabase() override = default;

    std::vector<int> loadCounters() override;
    void saveCounters(const std::vector<int>& counters) override;

private:
    struct ThreadLocalDB {
        QSqlDatabase db;
        bool initialized = false;
    };

    void initializeDB(QSqlDatabase& db);
    ThreadLocalDB* getThreadLocalDB();
    bool ensureDatabaseOpen(ThreadLocalDB* localDB);

    QString m_databaseName;
    std::unique_ptr<IDatabaseInitializer> m_initializer;
    std::unique_ptr<ThreadLocalDB> m_threadLocalDB;
};

#endif // SQLITEDATABASE_H
