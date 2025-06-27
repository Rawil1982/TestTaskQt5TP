#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "idatabase.h"
#include <QString>
#include <memory>

class QSqlDatabase;

class SQLiteDatabase : public IDatabase {
public:
    explicit SQLiteDatabase(const QString& databasePath);
    ~SQLiteDatabase() override;
    
    std::vector<int> loadCounters() override;
    void saveCounters(const std::vector<int>& counters) override;
    bool isOpen() const override;
    
private:
    QString m_databasePath;
    QSqlDatabase* m_database;
    
    void initializeDatabase();
    void createTables();
};

#endif // SQLITEDATABASE_H 