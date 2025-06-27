#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <memory>
#include <thread>
#include "presentation/viewmodels/countersviewmodel.h"
#include "presentation/models/counterstablemodel.h"
#include "infrastructure/workers/incrementworker.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(std::shared_ptr<CountersViewModel> viewModel, 
                      std::unique_ptr<IncrementWorker> worker,
                      QWidget* parent = nullptr);
    ~MainWindow() override;
    
private slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onSaveButtonClicked();
    void onCountersChanged();
    void onFrequencyChanged();
    void updateTable();
    
private:
    void setupUI();
    void setupConnections();
    
    std::shared_ptr<CountersViewModel> m_viewModel;
    std::unique_ptr<IncrementWorker> m_worker;
    std::unique_ptr<std::thread> m_workerThread;
    
    QTableView* m_tableView;
    CountersTableModel* m_tableModel;
    QLabel* m_frequencyLabel;
    QPushButton* m_addButton;
    QPushButton* m_removeButton;
    QPushButton* m_saveButton;
    QTimer* m_updateTimer;
};

#endif // MAINWINDOW_H 