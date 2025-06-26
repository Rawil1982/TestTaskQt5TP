#ifndef IDATABASEINITIALIZER_H
#define IDATABASEINITIALIZER_H

#include <QSqlDatabase>
#include <QString>

class IDatabaseInitializer {
public:
    virtual ~IDatabaseInitializer() = default;
    virtual bool initialize(QSqlDatabase& db, const QString& databaseName) = 0;
    virtual bool createTables(QSqlDatabase& db) = 0;
    virtual QString getConnectionName() const = 0;
};

#endif 