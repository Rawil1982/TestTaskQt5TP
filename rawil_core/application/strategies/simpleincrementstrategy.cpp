#include "simpleincrementstrategy.h"

SimpleIncrementStrategy::SimpleIncrementStrategy()
{
}

int SimpleIncrementStrategy::increment(int currentValue)
{
    return currentValue + 1;
} 