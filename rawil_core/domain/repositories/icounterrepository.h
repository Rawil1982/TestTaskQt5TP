#ifndef ICOUNTERREPOSITORY_H
#define ICOUNTERREPOSITORY_H

#include <vector>
#include <memory>
#include "domain/entities/counter.h"

class ICounterRepository {
public:
    virtual ~ICounterRepository() = default;
    
    virtual std::vector<Counter> getAllCounters() const = 0;
    virtual void saveCounters(const std::vector<Counter>& counters) = 0;
    virtual void addCounter(const Counter& counter) = 0;
    virtual void removeCounter(const int id) = 0;
    virtual void updateCounter(const Counter& counter) = 0;
    virtual Counter getCounterById(const int id) const = 0;
};

#endif // ICOUNTERREPOSITORY_H 