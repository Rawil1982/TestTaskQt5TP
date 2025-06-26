#include "headers/sqlitedatabaseinitializer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <sstream>
#include <iomanip>

SQLiteDatabaseInitializer::SQLiteDatabaseInitializer() {
    generateConnectionName();
}

void SQLiteDatabaseInitializer::generateConnectionName() {
    std::thread::id threadId = std::this_thread::get_id();
    std::stringstream ss;
    ss << std::hex << threadId;
    m_connectionName = QString("conn_%1").arg(QString::fromStdString(ss.str()));
}

QString SQLiteDatabaseInitializer::getConnectionName() const {
    return m_connectionName;
}

bool SQLiteDatabaseInitializer::initialize(QSqlDatabase& db, const QString& databaseName) {
    if (db.isOpen()) return true;

    db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    db.setDatabaseName(databaseName);

    if (!db.open()) {
        qCritical() << QObject::tr("Thread [ %0 ] Database open error:").arg(m_connectionName)
                    << db.lastError().text();
        return false;
    }

    qDebug() << QObject::tr("Thread [ %0 ] Database opened successfully").arg(m_connectionName);
    return true;
}

bool SQLiteDatabaseInitializer::createTables(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qCritical() << QObject::tr("Database not open in thread") << m_connectionName;
        return false;
    }

    QSqlQuery query(db);
    QString createTable = "CREATE TABLE IF NOT EXISTS counters ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "value INTEGER NOT NULL)";

    if (!query.exec(createTable)) {
        qCritical() << QObject::tr("Thread [ %0 ] Create table error:").arg(m_connectionName)
                    << query.lastError().text();
        return false;
    }

    return true;
} 