#ifndef COUNTERREPOSITORY_H
#define COUNTERREPOSITORY_H

#include "icounterrepository.h"
#include <memory>
#include <QMutex>

class IDatabase;

class CounterRepository : public ICounterRepository {
public:
    explicit CounterRepository(std::shared_ptr<IDatabase> database);
    ~CounterRepository() override = default;
    
    std::vector<Counter> getAllCounters() const override;
    void saveCounters(const std::vector<Counter>& counters) override;
    void addCounter(const Counter& counter) override;
    void removeCounter(const int id) override;
    void updateCounter(const Counter& counter) override;
    Counter getCounterById(const int id) const override;
    
private:
    std::shared_ptr<IDatabase> m_database;
    mutable QMutex m_mutex;
    std::vector<Counter> m_counters;
    int m_nextId;
    
    void loadCountersFromDatabase();
};

#endif // COUNTERREPOSITORY_H 