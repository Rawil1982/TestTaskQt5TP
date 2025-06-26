#ifndef COUNTERMANAGER_H
#define COUNTERMANAGER_H

#include <vector>
#include <mutex>

class CounterManager {
public:
    void addCounter(int initialValue = 0);
    void removeCounter(int index);
    void incrementAll();
    std::vector<int> getCounters() const;
    double getSum() const;
    int getCounter(int index) const;
    int size() const;

private:
    mutable std::mutex m_mutex;
    std::vector<int> m_counters; // Просто вектор int
};

#endif // COUNTERMANAGER_H
