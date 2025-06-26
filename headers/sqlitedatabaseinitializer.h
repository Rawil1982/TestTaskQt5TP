#ifndef SQLITEDATABASEINITIALIZER_H
#define SQLITEDATABASEINITIALIZER_H

#include "headers/interfaces/idatabaseinitializer.h"
#include <QSqlDatabase>
#include <QString>
#include <thread>

class SQLiteDatabaseInitializer : public IDatabaseInitializer {
public:
    SQLiteDatabaseInitializer();
    ~SQLiteDatabaseInitializer() override = default;

    bool initialize(QSqlDatabase& db, const QString& databaseName) override;
    bool createTables(QSqlDatabase& db) override;
    QString getConnectionName() const override;

private:
    QString m_connectionName;
    void generateConnectionName();
};

#endif // SQLITEDATABASEINITIALIZER_H 