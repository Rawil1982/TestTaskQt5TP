#ifndef COUNTERSERVICE_H
#define COUNTERSERVICE_H

#include <memory>
#include <vector>
#include "domain/entities/counter.h"
#include "domain/repositories/icounterrepository.h"
#include "domain/services/ifrequencycalculator.h"

class CounterService {
public:
    CounterService(std::shared_ptr<ICounterRepository> repository,
                  std::unique_ptr<IFrequencyCalculator> frequencyCalculator);
    ~CounterService() = default;
    
    std::vector<Counter> getAllCounters() const;
    void addCounter(const Counter& counter);
    void removeCounter(int id);
    void saveCounters();
    double calculateFrequency(const std::vector<int>& currentValues, 
                            const std::vector<int>& previousValues,
                            const std::chrono::milliseconds& timeDiff);
    
private:
    std::shared_ptr<ICounterRepository> m_repository;
    std::unique_ptr<IFrequencyCalculator> m_frequencyCalculator;
};

#endif // COUNTERSERVICE_H 