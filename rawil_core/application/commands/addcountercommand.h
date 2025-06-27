#ifndef ADDCOUNTERCOMMAND_H
#define ADDCOUNTERCOMMAND_H

#include <QString>
#include "icommand.h"
#include "domain/repositories/icounterrepository.h"
#include "domain/entities/counter.h"

class AddCounterCommand : public ICommand
{
public:
    AddCounterCommand(ICounterRepository* repository, int id, int initialValue = 0);
    void execute() override;

private:
    ICounterRepository* m_repository;
    int m_id;
    int m_initialValue;
};

#endif // ADDCOUNTERCOMMAND_H 