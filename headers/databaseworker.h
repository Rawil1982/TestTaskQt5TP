#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include "headers/interfaces/iworker.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>

// Forward declarations
class IDatabase;

class DatabaseWorker : public IWorker {
    Q_OBJECT

public:
    explicit DatabaseWorker(std::unique_ptr<IDatabase> database);
    ~DatabaseWorker() override;

    void start() override;
    void stop() override;
    bool isRunning() const override;
    
    void loadCounters();
    void saveCounters(const std::vector<int>& counters);

signals:
    void countersLoaded(const std::vector<int>& counters);
    void countersSaved();

private:
    void run();
    void addTask(std::function<void()> task);

    std::unique_ptr<IDatabase> m_database;
    std::thread m_workerThread;
    std::atomic_bool m_running;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<std::function<void()>> m_tasks;
};

#endif // DATABASEWORKER_H
