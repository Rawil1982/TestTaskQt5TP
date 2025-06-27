#ifndef COUNTERSTABLEMODEL_H
#define COUNTERSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <memory>
#include "domain/entities/counter.h"

class CountersTableModel : public QAbstractTableModel {
    Q_OBJECT
    
public:
    explicit CountersTableModel(QObject* parent = nullptr);
    ~CountersTableModel() = default;
    
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const override;
    QVariant headerData(const int section, const Qt::Orientation orientation, const int role = Qt::DisplayRole) const override;
    
    void setCounters(const QVector<Counter>& counters);
    void updateCounter(const int row, const Counter& counter);
    
private:
    QVector<Counter> m_counters;
};

#endif // COUNTERSTABLEMODEL_H 