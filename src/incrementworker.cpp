#include "headers/incrementworker.h"

IncrementWorker::IncrementWorker(CounterManager& manager, QObject* parent)
    : QObject(parent), m_counterManager(manager), m_running(false) {}

IncrementWorker::~IncrementWorker() {
    stop();
}

void IncrementWorker::start() {
    if (m_running) return;
    m_running = true;
    m_workerThread = std::thread(&IncrementWorker::run, this);
}

void IncrementWorker::stop() {
    if (!m_running) return;
    m_running = false;
    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
}

void IncrementWorker::run() {
    using namespace std::chrono;

    constexpr auto interval = 200ms; // 5 обновлений в секунду. Надо убрать хардкод (?) или вынести выше

    while (m_running) {
        auto start = steady_clock::now();

        m_counterManager.incrementAll();
        emit dataChanged();

        auto end = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(end - start);
        auto sleepTime = interval - elapsed;

        if (sleepTime > 0ms) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}
