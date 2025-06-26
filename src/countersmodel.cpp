#include "headers/countersmodel.h"
#include "headers/countermanager.h"
#include "headers/interfaces/idatabase.h"

CountersModel::CountersModel(CounterManager& manager, QObject *parent)
    : QAbstractTableModel(parent), m_counterManager(manager) {}

int CountersModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_counterManager.size();
}

int CountersModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 1;
}

QVariant CountersModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    return m_counterManager.getCounter(index.row());
}

QVariant CountersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    return section == 0 ? tr("Значение") : QVariant();
}

void CountersModel::addCounters(const std::vector<int>& counters) {
    if (counters.empty()) return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + static_cast<int>(counters.size()) - 1);
    for (int value : counters) {
        m_counterManager.addCounter(value);
    }
    endInsertRows();
}

void CountersModel::insertRow(int row) {
    beginInsertRows(QModelIndex(), row, row);
    m_counterManager.addCounter();
    endInsertRows();
}

void CountersModel::removeRow(int row) {
    if (row < 0 || row >= rowCount()) return;

    beginRemoveRows(QModelIndex(), row, row);
    m_counterManager.removeCounter(row);
    endRemoveRows();
}

std::vector<int> CountersModel::getCounters() const {
    return m_counterManager.getCounters();
}

void CountersModel::refreshData() {
    if (rowCount() > 0) {
        emit dataChanged(index(0, 0),
                         index(rowCount()-1, columnCount()-1));
    }
}


