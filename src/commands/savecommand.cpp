#include "headers/commands/savecommand.h"
#include "headers/countersmodel.h"
#include "headers/databaseworker.h"

SaveCommand::SaveCommand(CountersModel& model, DatabaseWorker& worker)
    : m_model(model), m_worker(worker) {}

void SaveCommand::execute() {
    m_worker.saveCounters(m_model.getCounters());
} 
