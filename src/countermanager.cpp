#include "headers/countermanager.h"
#include "headers/simpleincrementstrategy.h"
#include "headers/interfaces/iincrementstrategy.h"
#include <stdexcept>

CounterManager::CounterManager(std::unique_ptr<IIncrementStrategy> strategy)
    : m_incrementStrategy(std::move(strategy)) {
    if (!m_incrementStrategy) {
        m_incrementStrategy = std::make_unique<SimpleIncrementStrategy>();
    }
}

void CounterManager::addCounter(int initialValue) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_counters.push_back(initialValue);
}

void CounterManager::removeCounter(int index) {
    std::lock_guard<std::mutex> lock(m_mutex);
    validateIndex(index);
    m_counters.erase(m_counters.begin() + index);
}

int CounterManager::getCounter(int index) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    validateIndex(index);
    return m_counters[index];
}

int CounterManager::size() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return static_cast<int>(m_counters.size());
}

std::vector<int> CounterManager::getCounters() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_counters;
}

void CounterManager::incrementAll() {
    std::lock_guard<std::mutex> lock(m_mutex);
    ensureStrategyExists();
    m_incrementStrategy->incrementAll(m_counters);
}

double CounterManager::getSum() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    double sum = 0.0;
    for (int value : m_counters) {
        sum += value;
    }
    return sum;
}

void CounterManager::setIncrementStrategy(std::unique_ptr<IIncrementStrategy> strategy) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_incrementStrategy = std::move(strategy);
}

void CounterManager::validateIndex(int index) const {
    if (index < 0 || index >= static_cast<int>(m_counters.size())) {
        throw std::out_of_range("Counter index out of range");
    }
}

void CounterManager::ensureStrategyExists() {
    if (!m_incrementStrategy) {
        m_incrementStrategy = std::make_unique<SimpleIncrementStrategy>();
    }
}
