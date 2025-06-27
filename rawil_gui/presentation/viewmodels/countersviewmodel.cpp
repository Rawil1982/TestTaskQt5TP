#include "countersviewmodel.h"
#include "domain/entities/counter.h"
#include <QDebug>

CountersViewModel::CountersViewModel(std::shared_ptr<CounterService> service, QObject* parent)
    : QObject(parent), m_service(service), m_currentFrequency(0.0) {
    updatePreviousValues();
}

void CountersViewModel::addCounter() {
    if (m_service) {
        Counter newCounter(0, 0);
        m_service->addCounter(newCounter);
        emit countersChanged();
    }
}

void CountersViewModel::removeCounter(int index) {
    if (m_service) {
        auto counters = m_service->getAllCounters();
        if (index >= 0 && index < static_cast<int>(counters.size())) {
            m_service->removeCounter(counters[index].getId());
            emit countersChanged();
        }
    }
}

void CountersViewModel::saveCounters() {
    if (m_service) {
        m_service->saveCounters();
    }
}

QString CountersViewModel::getFrequencyText() const {
    return QString("Частота инкрементирования: %1 счетчиков/сек").arg(m_currentFrequency, 0, 'f', 2);
}

std::vector<int> CountersViewModel::getCounterValues() const {
    if (m_service) {
        auto counters = m_service->getAllCounters();
        std::vector<int> values;
        for (const auto& counter : counters) {
            values.push_back(counter.getValue());
        }
        return values;
    }
    return {};
}

void CountersViewModel::updateFrequency() {
    if (!m_service) {
        return;
    }
    
    auto currentValues = getCounterValues();
    auto now = std::chrono::high_resolution_clock::now();
    
    if (m_lastUpdate.time_since_epoch().count() > 0) {
        auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastUpdate);
        m_currentFrequency = m_service->calculateFrequency(currentValues, m_previousValues, timeDiff);
        emit frequencyChanged();
    }
    
    updatePreviousValues();
    m_lastUpdate = now;
}

void CountersViewModel::updatePreviousValues() {
    m_previousValues = getCounterValues();
} 