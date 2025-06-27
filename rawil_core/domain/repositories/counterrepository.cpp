#include "counterrepository.h"
#include "infrastructure/database/idatabase.h"
#include <algorithm>

namespace {
    constexpr int DEFAULT_NEXT_ID = 1;
    constexpr int INVALID_ID = 0;
    constexpr int ID_INCREMENT = 1;
}

CounterRepository::CounterRepository(std::shared_ptr<IDatabase> database)
    : m_database(database), m_nextId(DEFAULT_NEXT_ID) {
    loadCountersFromDatabase();
}

std::vector<Counter> CounterRepository::getAllCounters() const {
    QMutexLocker locker(&m_mutex);
    return m_counters;
}

void CounterRepository::saveCounters(const std::vector<Counter>& counters) {
    QMutexLocker locker(&m_mutex);
    m_counters = counters;
    if (m_database) {
        std::vector<int> values;
        values.reserve(counters.size());
        for (const auto& counter : counters) {
            values.push_back(counter.getValue());
        }
        m_database->saveCounters(values);
    }
}

void CounterRepository::addCounter(const Counter& counter) {
    QMutexLocker locker(&m_mutex);
    Counter newCounter = counter;
    if (newCounter.getId() == INVALID_ID) {
        newCounter.setId(m_nextId++);
    }
    m_counters.push_back(newCounter);
}

void CounterRepository::removeCounter(const int id) {
    QMutexLocker locker(&m_mutex);
    m_counters.erase(
        std::remove_if(m_counters.begin(), m_counters.end(),
                      [id](const Counter& counter) { return counter.getId() == id; }),
        m_counters.end()
    );
}

void CounterRepository::updateCounter(const Counter& counter) {
    QMutexLocker locker(&m_mutex);
    auto it = std::find_if(m_counters.begin(), m_counters.end(),
                          [&counter](const Counter& c) { return c.getId() == counter.getId(); });
    if (it != m_counters.end()) {
        *it = counter;
    }
}

Counter CounterRepository::getCounterById(const int id) const {
    QMutexLocker locker(&m_mutex);
    auto it = std::find_if(m_counters.begin(), m_counters.end(),
                          [id](const Counter& counter) { return counter.getId() == id; });
    if (it != m_counters.end()) {
        return *it;
    }
    return Counter();
}

void CounterRepository::loadCountersFromDatabase() {
    if (m_database) {
        const std::vector<int> values = m_database->loadCounters();
        for (size_t i = 0; i < values.size(); ++i) {
            const Counter counter(static_cast<int>(i + 1), values[i]);
            m_counters.push_back(counter);
            if (counter.getId() >= m_nextId) {
                m_nextId = counter.getId() + ID_INCREMENT;
            }
        }
    }
} 