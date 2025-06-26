#ifndef COMMANDS_H
#define COMMANDS_H

#include "countermanager.h"
#include "countersmodel.h"
#include "databaseworker.h"
#include <QItemSelectionModel>
#include <QMessageBox>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

class AddCommand : public ICommand {
public:
    AddCommand(CounterManager& m_manager, CountersModel& m_model);
    void execute() override;

private:
    CounterManager& m_manager;
    CountersModel& m_model;
};

class RemoveCommand : public ICommand {
public:
    RemoveCommand(CounterManager& m_manager, CountersModel& m_model, QItemSelectionModel* m_selection);
    void execute() override;

private:
    CounterManager& m_manager;
    CountersModel& m_model;
    QItemSelectionModel* m_selection;
};

class SaveCommand : public ICommand {
public:
    SaveCommand(CountersModel& m_model, DatabaseWorker& m_worker);
    void execute() override;

private:
    CountersModel& m_model;
    DatabaseWorker& m_worker;
};

#endif // COMMANDS_H
