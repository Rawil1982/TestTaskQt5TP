#include "../headers/commands.h"

AddCommand::AddCommand(CounterManager &manager, CountersModel &model)
    : m_manager(manager), m_model(model) {}

void AddCommand::execute() {
    m_manager.addCounter();
    m_model.insertRow(m_model.rowCount());
}

RemoveCommand::RemoveCommand(CounterManager &manager, CountersModel &model, QItemSelectionModel *selection)
    : m_manager(manager), m_model(model), m_selection(selection) {}

void RemoveCommand::execute() {
    if (!m_selection) return;
    QModelIndexList selected = m_selection->selectedRows();
    if (selected.isEmpty()) return;

    // Собираем индексы для удаления
    std::vector<int> rows;
    for (const auto& index : selected) {
        rows.push_back(index.row());
    }

    // Сортируем в обратном порядке
    std::sort(rows.rbegin(), rows.rend());

    for (int row : rows) {
        if (row >= 0 && row < m_model.rowCount()) {
            m_model.beginRemoveRows(QModelIndex(), row, row);
            m_manager.removeCounter(row);
            m_model.endRemoveRows();
        }
    }
}

SaveCommand::SaveCommand(CountersModel &model, DatabaseWorker &worker)
    : m_model(model), m_worker(worker) {}

void SaveCommand::execute() {
    m_worker.saveCounters(m_model.getCounters());
}
