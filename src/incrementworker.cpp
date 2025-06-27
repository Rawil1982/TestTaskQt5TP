#include "headers/incrementworker.h"
#include "headers/countermanager.h"
#include "headers/interfaces/iworker.h"

IncrementWorker::IncrementWorker(CounterManager& manager, QObject* parent)
    : IWorker(parent), m_counterManager(manager), m_running(false) {}

IncrementWorker::~IncrementWorker() {
    stop();
}

void IncrementWorker::start() {
    if (m_running) return;
    m_running = true;
    m_workerThread = std::thread(&IncrementWorker::run, this);
    emit started();
}

void IncrementWorker::stop() {
    if (!m_running) return;
    m_running = false;
    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
    emit stopped();
}

bool IncrementWorker::isRunning() const {
    return m_running;
}

const char *IncrementWorker::getWorkerName() const
{
    return m_workerName;
}

void IncrementWorker::run() {
    using namespace std::chrono;

    constexpr auto interval = 200ms; // 5 обновлений в секунду. Потом вынесу в переменные или в constexpr

    while (m_running) {
        auto start = steady_clock::now();

        try {
            m_counterManager.incrementAll();
            emit dataChanged();
        } catch (const std::exception& e) {
            emit error(QString("Increment error: %1").arg(e.what()));
        }

        auto end = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(end - start);
        auto sleepTime = interval - elapsed;

        if (sleepTime > 0ms) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}
