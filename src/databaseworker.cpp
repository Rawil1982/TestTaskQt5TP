#include "headers/databaseworker.h"
#include <QMetaType>

DatabaseWorker::DatabaseWorker(std::unique_ptr<IDatabase> database)
    : m_database(std::move(database)), m_running(false) {
    // Регистрируем тип для межпоточных сгиналов/слотов. По идее, надо перенести в какой-нибудь RegisterMetatypesManager
    qRegisterMetaType<std::vector<int>>("std::vector<int>");
}

DatabaseWorker::~DatabaseWorker() {
    stop();
}

void DatabaseWorker::start() {
    if (m_running) return;
    m_running = true;
    m_workerThread = std::thread(&DatabaseWorker::run, this);
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
}

void DatabaseWorker::loadCounters() {
    addTask([this]() {
        auto counters = m_database->loadCounters();
        emit countersLoaded(counters);
    });
}

void DatabaseWorker::saveCounters(const std::vector<int>& counters) {
    addTask([this, counters]() {
        m_database->saveCounters(counters);
        emit countersSaved();
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
    // Закрываем все соединения этого потока
    if (m_database) {
        // Для SQLiteDatabase это происходит автоматически,
        // но можно добавить явный метод очистки
    }
}
