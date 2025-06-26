#include "headers/countermanager.h"

void CounterManager::addCounter(int initialValue) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_counters.push_back(initialValue);
}

void CounterManager::removeCounter(int index) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (index >= 0 && static_cast<size_t>(index) < m_counters.size()) {
        m_counters.erase(m_counters.begin() + index);
    }
}

void CounterManager::incrementAll() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& counter : m_counters) {
        ++counter;
    }
}

std::vector<int> CounterManager::getCounters() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_counters;
}

double CounterManager::getSum() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    double sum = 0;
    for (const auto& counter : m_counters) {
        sum += counter;
    }
    return sum;
}

int CounterManager::getCounter(int index) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (index >= 0 && static_cast<size_t>(index) < m_counters.size()) {
        return m_counters[index];
    }
    return 0;
}

int CounterManager::size() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_counters.size();
}
