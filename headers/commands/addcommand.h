#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "headers/commands/icommand.h"

// Forward declarations
class CounterManager;
class CountersModel;

class AddCommand : public ICommand {
public:
    AddCommand(CounterManager& manager, CountersModel& model);
    // ICommand interface
    void execute() override;

private:
    CounterManager& m_manager;
    CountersModel& m_model;
};

#endif 
