#ifndef COUNTERMANAGER_H
#define COUNTERMANAGER_H

#include <vector>
#include <mutex>
#include <memory>

// Forward declarations
class IIncrementStrategy;

class CounterManager {
public:
    explicit CounterManager(std::unique_ptr<IIncrementStrategy> strategy = nullptr);
    ~CounterManager() = default;

    // Управление счетчиками
    void addCounter(int initialValue = 0);
    void removeCounter(int index);
    int getCounter(int index) const;
    int size() const;
    std::vector<int> getCounters() const;
    
    // Операции со счетчиками
    void incrementAll();
    void increment(int index);
    
    // Вычисления
    double getSum() const;
    
    // Управление стратегией
    void setIncrementStrategy(std::unique_ptr<IIncrementStrategy> strategy);

private:
    mutable std::mutex m_mutex;
    std::vector<int> m_counters;
    std::unique_ptr<IIncrementStrategy> m_incrementStrategy;
    
    // Приватные методы для внутренней логики
    void validateIndex(int index) const;
    void ensureStrategyExists();
};

#endif // COUNTERMANAGER_H
