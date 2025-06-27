#include "headers/simpleincrementstrategy.h"

void SimpleIncrementStrategy::incrementAll(std::vector<int>& counters) {
    for (auto& counter : counters) {
        counter++;
    }
} 
