#include "addcountercommand.h"

AddCounterCommand::AddCounterCommand(ICounterRepository* repository, int id, int initialValue)
    : m_repository(repository), m_id(id), m_initialValue(initialValue)
{
}

void AddCounterCommand::execute()
{
    if (m_repository) {
        Counter counter(m_id, m_initialValue);
        m_repository->addCounter(counter);
    }
} 