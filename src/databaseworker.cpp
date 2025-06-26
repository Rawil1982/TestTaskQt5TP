#include "headers/databaseworker.h"
#include "headers/interfaces/idatabase.h"
#include <QMetaType>

DatabaseWorker::DatabaseWorker(std::unique_ptr<IDatabase> database)
    : m_database(std::move(database)), m_running(false) {
    qRegisterMetaType<std::vector<int>>("std::vector<int>");
}

DatabaseWorker::~DatabaseWorker() {
    stop();
}

void DatabaseWorker::start() {
    if (m_running) return;
    m_running = true;
    m_workerThread = std::thread(&DatabaseWorker::run, this);
    emit started();
}

void DatabaseWorker::stop() {
    if (!m_running) return;

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_running = false;
    }
    m_cv.notify_one();

    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
    emit stopped();
}

bool DatabaseWorker::isRunning() const {
    return m_running;
}

void DatabaseWorker::loadCounters() {
    addTask([this]() {
        try {
            auto counters = m_database->loadCounters();
            emit countersLoaded(counters);
        } catch (const std::exception& e) {
            emit error(QString("Load counters error: %1").arg(e.what()));
        }
    });
}

void DatabaseWorker::saveCounters(const std::vector<int>& counters) {
    addTask([this, counters]() {
        try {
            m_database->saveCounters(counters);
            emit countersSaved();
        } catch (const std::exception& e) {
            emit error(QString("Save counters error: %1").arg(e.what()));
        }
    });
}

void DatabaseWorker::addTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_tasks.push(std::move(task));
    }
    m_cv.notify_one();
}

void DatabaseWorker::run() {
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return !m_tasks.empty() || !m_running; });

        if (!m_running) break;

        auto task = std::move(m_tasks.front());
        m_tasks.pop();
        lock.unlock();

        task();
    }
}
