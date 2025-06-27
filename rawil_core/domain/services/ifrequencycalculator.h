#ifndef IFREQUENCYCALCULATOR_H
#define IFREQUENCYCALCULATOR_H

#include <vector>
#include <chrono>

class IFrequencyCalculator {
public:
    virtual ~IFrequencyCalculator() = default;
    
    virtual double calculateFrequency(const std::vector<int>& currentValues, 
                                    const std::vector<int>& previousValues,
                                    const std::chrono::milliseconds& timeDiff) = 0;
};

#endif // IFREQUENCYCALCULATOR_H 