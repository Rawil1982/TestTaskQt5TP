#include "sqlitedatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SQLiteDatabase::SQLiteDatabase(const QString& databasePath)
    : m_databasePath(databasePath), m_database(nullptr) {
    initializeDatabase();
}

SQLiteDatabase::~SQLiteDatabase() {
    if (m_database) {
        m_database->close();
        delete m_database;
    }
}

std::vector<int> SQLiteDatabase::loadCounters() {
    std::vector<int> counters;
    
    if (!isOpen()) {
        return counters;
    }
    
    QSqlQuery query(*m_database);
    query.exec("SELECT value FROM counters ORDER BY id");
    
    while (query.next()) {
        counters.push_back(query.value(0).toInt());
    }
    
    return counters;
}

void SQLiteDatabase::saveCounters(const std::vector<int>& counters) {
    if (!isOpen()) {
        return;
    }
    
    m_database->transaction();
    
    QSqlQuery query(*m_database);
    query.exec("DELETE FROM counters");
    
    query.prepare("INSERT INTO counters (id, value) VALUES (?, ?)");
    for (size_t i = 0; i < counters.size(); ++i) {
        query.addBindValue(static_cast<int>(i + 1));
        query.addBindValue(counters[i]);
        query.exec();
    }
    
    m_database->commit();
}

bool SQLiteDatabase::isOpen() const {
    return m_database && m_database->isOpen();
}

void SQLiteDatabase::initializeDatabase() {
    m_database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_database->setDatabaseName(m_databasePath);
    
    if (!m_database->open()) {
        qDebug() << "Failed to open database:" << m_database->lastError().text();
        return;
    }
    
    createTables();
}

void SQLiteDatabase::createTables() {
    QSqlQuery query(*m_database);
    query.exec("CREATE TABLE IF NOT EXISTS counters (id INTEGER PRIMARY KEY, value INTEGER)");
} 