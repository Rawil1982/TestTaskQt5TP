#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H

#include "headers/commands/icommand.h"
#include <QItemSelectionModel>

class CounterManager;
class CountersModel;

class RemoveCommand : public ICommand {
public:
    RemoveCommand(CounterManager& manager, CountersModel& model, QItemSelectionModel* selection);
    void execute() override;

private:
    CounterManager& m_manager;
    CountersModel& m_model;
    QItemSelectionModel* m_selection;
};

#endif 