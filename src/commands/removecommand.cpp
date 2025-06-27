#include "headers/commands/removecommand.h"
#include "headers/countermanager.h"
#include "headers/countersmodel.h"
#include <algorithm>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QModelIndexList>

RemoveCommand::RemoveCommand(CounterManager& manager, CountersModel& model, QItemSelectionModel* selection)
    : m_manager(manager), m_model(model), m_selection(selection) {}

void RemoveCommand::execute() {
    if (!m_selection) return;
    const QModelIndexList selected = m_selection->selectedRows();
    if (selected.isEmpty()) return;

    std::vector<int> rows;
    for (const auto& index : selected) {
        rows.push_back(index.row());
    }

    std::sort(rows.rbegin(), rows.rend());

    for (int row : rows) {
        if (row >= 0 && row < m_model.rowCount()) {
            m_model.beginRemoveRows(QModelIndex(), row, row);
            m_manager.removeCounter(row);
            m_model.endRemoveRows();
        }
    }
} 
