#include "headers/sqlitedatabase.h"
#include "headers/interfaces/idatabaseinitializer.h"
#include "headers/sqlitedatabaseinitializer.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <thread>
#include <utility>
#include <sstream>
#include <iomanip>

thread_local std::unique_ptr<SQLiteDatabase::ThreadLocalDB> SQLiteDatabase::m_threadLocalDB;

SQLiteDatabase::SQLiteDatabase(QString databaseName, 
                               std::unique_ptr<IDatabaseInitializer> initializer)
    : m_databaseName(std::move(databaseName))
    , m_initializer(std::move(initializer)) {
    if (!m_initializer) {
        m_initializer = std::make_unique<SQLiteDatabaseInitializer>();
    }
}

void SQLiteDatabase::initializeDB(QSqlDatabase& db) {
    if (db.isOpen()) return;

    if (!m_initializer->initialize(db, m_databaseName)) {
        return;
    }

    if (!m_initializer->createTables(db)) {
        return;
    }
}

SQLiteDatabase::ThreadLocalDB* SQLiteDatabase::getThreadLocalDB() {
    if (!m_threadLocalDB) {
        m_threadLocalDB = std::make_unique<ThreadLocalDB>();
    }
    return m_threadLocalDB.get();
}

bool SQLiteDatabase::ensureDatabaseOpen(ThreadLocalDB* localDB) {
    if (!localDB->db.isOpen()) {
        qCritical() << QObject::tr("Database not open in thread") << m_initializer->getConnectionName();
        return false;
    }
    return true;
}

std::vector<int> SQLiteDatabase::loadCounters() {
    ThreadLocalDB* localDB = getThreadLocalDB();
    initializeDB(localDB->db);

    if (!ensureDatabaseOpen(localDB)) {
        return {};
    }

    std::vector<int> counters;
    QSqlQuery query("SELECT value FROM counters", localDB->db);
    while (query.next()) {
        counters.push_back(query.value(0).toInt());
    }
    return counters;
}

void SQLiteDatabase::saveCounters(const std::vector<int>& counters) {
    ThreadLocalDB* localDB = getThreadLocalDB();
    initializeDB(localDB->db);

    if (!ensureDatabaseOpen(localDB)) {
        return;
    }

    QSqlQuery query(localDB->db);
    localDB->db.transaction();

    if (!query.exec("DELETE FROM counters")) {
        qWarning() << QObject::tr("Delete error:") << query.lastError().text();
    }

    query.prepare("INSERT INTO counters (value) VALUES (?)");
    for (int value : counters) {
        query.bindValue(0, value);
        if (!query.exec()) {
            qWarning() << QObject::tr("Insert error:") << query.lastError().text();
        }
    }

    if (!localDB->db.commit()) {
        qCritical() << QObject::tr("Commit error:") << localDB->db.lastError().text();
    }
}
