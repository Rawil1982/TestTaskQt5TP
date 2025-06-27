#ifndef FREQUENCYUPDATER_H
#define FREQUENCYUPDATER_H

#include <memory>
#include <cstdint>

class CounterManager;

class FrequencyUpdater {

public:
    FrequencyUpdater(CounterManager& manager, int updatePeriod);

    double updateFrequency();

private:
    CounterManager& m_counterManager;
    int m_updatePeriod;
    double m_lastFrequency = 0;
    double m_lastTime = 0;
    int m_lastSum = 0;
};

#endif // FREQUENCYUPDATER_H
