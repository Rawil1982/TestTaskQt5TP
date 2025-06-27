#ifndef IINCREMENTSTRATEGY_H
#define IINCREMENTSTRATEGY_H

class IIncrementStrategy
{
public:
    virtual ~IIncrementStrategy() = default;
    virtual int increment(int currentValue) = 0;
};

#endif // IINCREMENTSTRATEGY_H 