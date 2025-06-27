#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include "headers/interfaces/iworkermanager.h"
#include "headers/interfaces/idatabase.h"
#include <memory>
#include <vector>

// Forward declarations
class IWorker;
class CounterManager;

// IWorkerManaget уже наследуется от QObject
class WorkerManager : public IWorkerManager {
    Q_OBJECT

public:
    explicit WorkerManager(CounterManager& counterManager,
                           std::unique_ptr<IDatabase> database,
                           QObject* parent = nullptr);

    // IWorkerManager interface
    ~WorkerManager() override;

    void startAll() override;
    void stopAll() override;
    void pauseAll() override;
    void resumeAll() override;

    // Геттеры для доступа к воркерам (IWorkerManager interface)
    IWorker* getDatabaseWorker() const override;
    IWorker* getIncrementWorker() const override;

private:
    // Настройка воркеров
    void setupWorkers();
    void connectWorkerSignals(IWorker* worker, const QString& workerName);

    CounterManager& m_counterManager;
    std::unique_ptr<IDatabase> m_database;
    std::vector<std::unique_ptr<IWorker>> m_workers;
    
    // Указатели на конкретные воркеры
    IWorker* m_databaseWorker;
    IWorker* m_incrementWorker;
};

#endif // WORKERMANAGER_H 
