#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "idatabase.h"
#include <QSqlDatabase>
#include <QString>
#include <QThreadStorage>

class SQLiteDatabase : public IDatabase {
public:
    explicit SQLiteDatabase(QString  m_databaseName);

    std::vector<int> loadCounters() override;
    void saveCounters(const std::vector<int>& counters) override;

private:
    struct ThreadLocalDB {
        QSqlDatabase db;
        bool initialized = false;
    };

    void initializeDB(QSqlDatabase& db);

    QString m_databaseName;
    QThreadStorage<ThreadLocalDB*> m_threadStorage;
};

#endif // SQLITEDATABASE_H
