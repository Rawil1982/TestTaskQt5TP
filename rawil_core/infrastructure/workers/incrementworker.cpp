#include "incrementworker.h"
#include "domain/repositories/icounterrepository.h"
#include "domain/entities/counter.h"
#include <QDebug>

namespace {
    constexpr std::chrono::milliseconds DEFAULT_INTERVAL(100);
}

IncrementWorker::IncrementWorker(std::shared_ptr<ICounterRepository> repository)
    : m_repository(repository), m_running(false), m_interval(DEFAULT_INTERVAL) {
}

IncrementWorker::~IncrementWorker() {
    stop();
}

void IncrementWorker::start() {
    if (m_running) {
        return;
    }
    
    m_running = true;
    m_thread = std::thread(&IncrementWorker::incrementLoop, this);
}

void IncrementWorker::stop() {
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void IncrementWorker::incrementLoop() {
    while (m_running) {
        if (m_repository) {
            auto counters = m_repository->getAllCounters();
            for (auto& counter : counters) {
                counter.increment();
                m_repository->updateCounter(counter);
            }
        }
        
        std::this_thread::sleep_for(m_interval);
    }
} 
