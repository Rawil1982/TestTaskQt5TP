#ifndef SIMPLEINCREMENTSTRATEGY_H
#define SIMPLEINCREMENTSTRATEGY_H

#include "iincrementstrategy.h"

class SimpleIncrementStrategy : public IIncrementStrategy
{
public:
    SimpleIncrementStrategy();
    int increment(int currentValue) override;
};

#endif // SIMPLEINCREMENTSTRATEGY_H 