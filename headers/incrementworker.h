#ifndef INCREMENTWORKER_H
#define INCREMENTWORKER_H

#include <thread>
#include <atomic>
#include <chrono>
#include <QObject>
#include "countermanager.h"

class IncrementWorker : public QObject {
    Q_OBJECT

public:
    explicit IncrementWorker(CounterManager& manager, QObject* parent = nullptr);
    ~IncrementWorker();

    void start();
    void stop();

signals:
    void dataChanged();

private:
    void run();

    CounterManager& m_counterManager;
    std::thread m_workerThread;
    std::atomic_bool m_running;
};

#endif // INCREMENTWORKER_H
