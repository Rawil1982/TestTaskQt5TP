#ifndef COUNTERSMODEL_H
#define COUNTERSMODEL_H

#include <QAbstractTableModel>
#include "countermanager.h"

class CountersModel : public QAbstractTableModel {
    Q_OBJECT
    friend class RemoveCommand;
public:
    explicit CountersModel(CounterManager& manager, QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent= QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addCounters(const std::vector<int>& counters);
    void insertRow(int row);
    void removeRow(int row);
    std::vector<int> getCounters() const;

public slots:
    void refreshData();

private:
    CounterManager& m_counterManager;
};

#endif // COUNTERSMODEL_H
