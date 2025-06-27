#include "headers/workermanager.h"
#include "headers/databaseworker.h"
#include "headers/incrementworker.h"
#include <QTimer>
#include <QDebug>

WorkerManager::WorkerManager(CounterManager& counterManager, 
                             std::unique_ptr<IDatabase> database,
                             QObject* parent)
    : IWorkerManager(parent)
    , m_counterManager(counterManager)
    , m_database(std::move(database))
    , m_databaseWorker(nullptr)
    , m_incrementWorker(nullptr) {
    setupWorkers();
}

WorkerManager::~WorkerManager() {
    stopAll();
}

void WorkerManager::setupWorkers() {
    auto dbWorker = std::make_unique<DatabaseWorker>(std::move(m_database));
    m_databaseWorker = dbWorker.get();
    connectWorkerSignals(m_databaseWorker, m_databaseWorker->getWorkerName());
    m_workers.push_back(std::move(dbWorker));

    auto incWorker = std::make_unique<IncrementWorker>(m_counterManager);
    m_incrementWorker = incWorker.get();
    connectWorkerSignals(m_incrementWorker, m_incrementWorker->getWorkerName());
    m_workers.push_back(std::move(incWorker));
}

void WorkerManager::connectWorkerSignals(IWorker* worker, const QString& workerName) {
    connect(worker, &IWorker::error, this, [this, workerName](const QString& error) {
        emit workerError(workerName, error);
    });
}

void WorkerManager::startAll() {
    for (auto& worker : m_workers) {
        worker->start();
    }
    emit allWorkersStarted();
}

void WorkerManager::stopAll() {
    for (auto& worker : m_workers) {
        worker->stop();
    }
    emit allWorkersStopped();
}

void WorkerManager::pauseAll() {
    // В будущем можно добавить состояние "пауза"
    stopAll();
}

void WorkerManager::resumeAll() {
    startAll();
}

IWorker* WorkerManager::getDatabaseWorker() const {
    return m_databaseWorker;
}

IWorker* WorkerManager::getIncrementWorker() const {
    return m_incrementWorker;
} 
