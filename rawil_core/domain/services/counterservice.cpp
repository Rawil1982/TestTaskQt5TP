#include "counterservice.h"
#include "domain/entities/counter.h"

CounterService::CounterService(std::shared_ptr<ICounterRepository> repository,
                             std::unique_ptr<IFrequencyCalculator> frequencyCalculator)
    : m_repository(repository), m_frequencyCalculator(std::move(frequencyCalculator)) {
}

std::vector<Counter> CounterService::getAllCounters() const {
    if (m_repository) {
        return m_repository->getAllCounters();
    }
    return {};
}

void CounterService::addCounter(const Counter& counter) {
    if (m_repository) {
        m_repository->addCounter(counter);
    }
}

void CounterService::removeCounter(int id) {
    if (m_repository) {
        m_repository->removeCounter(id);
    }
}

void CounterService::saveCounters() {
    if (m_repository) {
        auto counters = m_repository->getAllCounters();
        m_repository->saveCounters(counters);
    }
}

double CounterService::calculateFrequency(const std::vector<int>& currentValues, 
                                        const std::vector<int>& previousValues,
                                        const std::chrono::milliseconds& timeDiff) {
    if (m_frequencyCalculator) {
        return m_frequencyCalculator->calculateFrequency(currentValues, previousValues, timeDiff);
    }
    return 0.0;
} 