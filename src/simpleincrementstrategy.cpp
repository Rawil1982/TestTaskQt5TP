#include "headers/simpleincrementstrategy.h"

void SimpleIncrementStrategy::increment(std::vector<int>& counters) {
    if (!counters.empty()) {
        counters[0]++;
    }
}

void SimpleIncrementStrategy::incrementAll(std::vector<int>& counters) {
    for (auto& counter : counters) {
        counter++;
    }
} 