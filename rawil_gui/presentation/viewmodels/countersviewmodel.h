#ifndef COUNTERSVIEWMODEL_H
#define COUNTERSVIEWMODEL_H

#include <QObject>
#include <QString>
#include <memory>
#include <vector>
#include <chrono>
#include "domain/services/counterservice.h"

class CountersViewModel : public QObject {
    Q_OBJECT
    
public:
    explicit CountersViewModel(std::shared_ptr<CounterService> service, QObject* parent = nullptr);
    ~CountersViewModel() = default;
    
    Q_INVOKABLE void addCounter();
    Q_INVOKABLE void removeCounter(int index);
    Q_INVOKABLE void saveCounters();
    Q_INVOKABLE QString getFrequencyText() const;
    
    std::vector<int> getCounterValues() const;
    void updateFrequency();
    
signals:
    void countersChanged();
    void frequencyChanged();
    
private:
    std::shared_ptr<CounterService> m_service;
    std::vector<int> m_previousValues;
    std::chrono::high_resolution_clock::time_point m_lastUpdate;
    double m_currentFrequency;
    
    void updatePreviousValues();
};

#endif // COUNTERSVIEWMODEL_H 