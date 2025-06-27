#include "headers/commands/addcommand.h"
#include "headers/countermanager.h"
#include "headers/countersmodel.h"

AddCommand::AddCommand(CounterManager& manager, CountersModel& model)
    : m_manager(manager), m_model(model) {}

void AddCommand::execute() {
    m_manager.addCounter();
    m_model.insertRow(m_model.rowCount());
} 
