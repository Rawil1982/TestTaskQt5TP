#ifndef FREQUENCYCALCULATOR_H
#define FREQUENCYCALCULATOR_H

#include "ifrequencycalculator.h"

class FrequencyCalculator : public IFrequencyCalculator {
public:
    FrequencyCalculator() = default;
    ~FrequencyCalculator() override = default;
    
    double calculateFrequency(const std::vector<int>& currentValues, 
                            const std::vector<int>& previousValues,
                            const std::chrono::milliseconds& timeDiff) override;
    
private:
    int calculateSum(const std::vector<int>& values) const;
};

#endif // FREQUENCYCALCULATOR_H 