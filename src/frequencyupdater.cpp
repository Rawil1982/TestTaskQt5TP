#include "headers/frequencyupdater.h"
#include "headers/countermanager.h"
#include <QDateTime>

FrequencyUpdater::FrequencyUpdater(CounterManager& manager,int updatePeriod)
    : m_counterManager(manager),
      m_updatePeriod(updatePeriod)
{
    m_lastTime = QDateTime::currentMSecsSinceEpoch();
    m_lastSum = m_counterManager.getSum();
}

double FrequencyUpdater::updateFrequency()
{
    const double currentTime = QDateTime::currentMSecsSinceEpoch();
    const double currentSum = m_counterManager.getSum();

    const double timeDelta = (currentTime - m_lastTime) / m_updatePeriod;
    const double sumDelta = currentSum - m_lastSum;

    const double frequency = timeDelta > 0 ? sumDelta / timeDelta : m_lastFrequency;
    m_lastFrequency = frequency;

    m_lastTime = currentTime;
    m_lastSum = currentSum;

    return frequency;
} 
