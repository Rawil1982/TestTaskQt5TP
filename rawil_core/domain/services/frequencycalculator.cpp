#include "frequencycalculator.h"
#include <numeric>
#include <algorithm>

double FrequencyCalculator::calculateFrequency(const std::vector<int>& currentValues, 
                                             const std::vector<int>& previousValues,
                                             const std::chrono::milliseconds& timeDiff) {
    if (timeDiff.count() <= 0) {
        return 0.0;
    }
    
    int currentSum = calculateSum(currentValues);
    int previousSum = calculateSum(previousValues);
    
    double timeDiffSeconds = timeDiff.count() / 1000.0;
    return (currentSum - previousSum) / timeDiffSeconds;
}

int FrequencyCalculator::calculateSum(const std::vector<int>& values) const {
    return std::accumulate(values.begin(), values.end(), 0);
} 