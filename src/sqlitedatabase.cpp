#include "headers/sqlitedatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QThread>
#include <utility> 
SQLiteDatabase::SQLiteDatabase(QString  databaseName)
    : m_databaseName(std::move(databaseName))
{

}

void SQLiteDatabase::initializeDB(QSqlDatabase& db) {
    if (db.isOpen()) return;

    QString connectionName = QObject::tr("conn_%1").arg(reinterpret_cast<quintptr>(QThread::currentThread()));
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(m_databaseName);

    if (!db.open()) {
        qCritical() << QObject::tr("Thread [ 0x%0 ] Database open error:").arg(reinterpret_cast<quintptr>(QThread::currentThread()), 0, 16)
                    << db.lastError().text();
        return;
    }

    qDebug() << QObject::tr("Thread [ 0x%0 ] Database opened successfully").arg(reinterpret_cast<quintptr>(QThread::currentThread()), 0, 16);

    // Создаем таблицу
    QSqlQuery query(db);
    QString createTable = "CREATE TABLE IF NOT EXISTS counters ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "value INTEGER NOT NULL)";

    if (!query.exec(createTable)) {
        qCritical() << QObject::tr("Thread [ 0x%0 ]  Create table error:").arg(reinterpret_cast<quintptr>(QThread::currentThread()), 0, 16)
                    << query.lastError().text();
    }
}

std::vector<int> SQLiteDatabase::loadCounters() {
    if (!m_threadStorage.hasLocalData()) {
        m_threadStorage.setLocalData(new ThreadLocalDB());
    }

    ThreadLocalDB* localDB = m_threadStorage.localData();
    initializeDB(localDB->db);

    if (!localDB->db.isOpen()) {
        qCritical() << QObject::tr("Database not open in thread") << QThread::currentThread();
        return {}; // Или выполнить повторную инициализацию
    }
    std::vector<int> counters;
    QSqlQuery query("SELECT value FROM counters", localDB->db);
    while (query.next()) {
        counters.push_back(query.value(0).toInt());
    }
    return counters;
}

void SQLiteDatabase::saveCounters(const std::vector<int>& counters) {
    if (!m_threadStorage.hasLocalData()) {
        m_threadStorage.setLocalData(new ThreadLocalDB());
    }

    ThreadLocalDB* localDB = m_threadStorage.localData();
    initializeDB(localDB->db);

    if (!localDB->db.isOpen()) {
        qCritical() << QObject::tr("Database not open in thread") << QThread::currentThread();
        return; // Или выполнить повторную инициализацию
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
