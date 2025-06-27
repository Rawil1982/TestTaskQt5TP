#ifndef INCREMENTWORKER_H
#define INCREMENTWORKER_H

#include "headers/interfaces/iworker.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <QObject>

// Forward declarations
class CounterManager;

class IncrementWorker : public IWorker {
    Q_OBJECT

public:
    explicit IncrementWorker(CounterManager& manager, QObject* parent = nullptr);
    // IWorker interface
    ~IncrementWorker() override;

    void start() override;
    void stop() override;
    bool isRunning() const override;
    const char *getWorkerName() const override;

private:
    void run();

    CounterManager& m_counterManager;
    std::thread m_workerThread;
    std::atomic_bool m_running;
    static constexpr const char* m_workerName = "IncrementWorker";
};

#endif // INCREMENTWORKER_H
