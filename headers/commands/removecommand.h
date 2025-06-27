#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H

#include "headers/commands/icommand.h"
#include <QItemSelectionModel>

// Forward declarations
class CounterManager;
class CountersModel;

class RemoveCommand : public ICommand {
public:
    RemoveCommand(CounterManager& manager, CountersModel& model, QItemSelectionModel* selection);
    // ICommand interface
    void execute() override;

private:
    CounterManager& m_manager;
    CountersModel& m_model;
    QItemSelectionModel* m_selection;
};

#endif 
