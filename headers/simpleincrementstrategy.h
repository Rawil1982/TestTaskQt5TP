#ifndef SIMPLEINCREMENTSTRATEGY_H
#define SIMPLEINCREMENTSTRATEGY_H

#include "headers/interfaces/iincrementstrategy.h"
#include <vector>

class SimpleIncrementStrategy : public IIncrementStrategy {
public:
    SimpleIncrementStrategy() = default;
    ~SimpleIncrementStrategy() override = default;

    void increment(std::vector<int>& counters) override;
    void incrementAll(std::vector<int>& counters) override;
};

#endif // SIMPLEINCREMENTSTRATEGY_H 