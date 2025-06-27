#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "headers/commands/icommand.h"

// Forward declarations
class CountersModel;
class DatabaseWorker;

class SaveCommand : public ICommand {
public:
    SaveCommand(CountersModel& model, DatabaseWorker& worker);
    // ICommand interface
    void execute() override;

private:
    CountersModel& m_model;
    DatabaseWorker& m_worker;
};

#endif 
