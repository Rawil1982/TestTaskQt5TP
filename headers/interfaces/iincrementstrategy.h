#ifndef IINCREMENTSTRATEGY_H
#define IINCREMENTSTRATEGY_H

#include <vector>

class IIncrementStrategy {
public:
    virtual ~IIncrementStrategy() = default;
    virtual void increment(std::vector<int>& counters) = 0;
    virtual void incrementAll(std::vector<int>& counters) = 0;
};

#endif 