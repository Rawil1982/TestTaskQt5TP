#include "counterstablemodel.h"
#include <QVariant>

namespace {
    constexpr int COLUMN_COUNT = 2;
    constexpr int ID_COLUMN = 0;
    constexpr int VALUE_COLUMN = 1;
}

CountersTableModel::CountersTableModel(QObject* parent)
    : QAbstractTableModel(parent) {
}

int CountersTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_counters.size();
}

int CountersTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return COLUMN_COUNT;
}

QVariant CountersTableModel::data(const QModelIndex& index, const int role) const {
    if (!index.isValid() || index.row() >= m_counters.size()) {
        return QVariant();
    }
    
    if (role == Qt::DisplayRole) {
        const Counter& counter = m_counters[index.row()];
        switch (index.column()) {
            case ID_COLUMN: return counter.getId();
            case VALUE_COLUMN: return counter.getValue();
            default: return QVariant();
        }
    }
    
    return QVariant();
}

QVariant CountersTableModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case ID_COLUMN: return tr("ID");
            case VALUE_COLUMN: return tr("Значение");
            default: return QVariant();
        }
    }
    
    return QVariant();
}

void CountersTableModel::setCounters(const QVector<Counter>& counters) {
    if (m_counters.size() == counters.size()) {
        m_counters = counters;
        if (!m_counters.isEmpty()) {
            emit dataChanged(index(0, 0), index(m_counters.size() - 1, columnCount() - 1));
        }
    } else {
        beginResetModel();
        m_counters = counters;
        endResetModel();
    }
}

void CountersTableModel::updateCounter(const int row, const Counter& counter) {
    if (row >= 0 && row < m_counters.size()) {
        m_counters[row] = counter;
        emit dataChanged(index(row, 0), index(row, 1));
    }
} 