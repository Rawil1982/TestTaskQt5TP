#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QTimer>
#include "headers/countermanager.h"
#include "headers/countersmodel.h"

// Forward declarations
class IDatabase;
class IWorkerManager;
class DatabaseWorker;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::unique_ptr<IDatabase> database, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // UI события
    void addCounter();
    void removeCounter();
    void saveCounters();
    void updateFrequency();
    
    // События от воркеров
    void onCountersLoaded(const std::vector<int>& counters);
    void onCountersSaved();
    void onWorkerError(const QString& workerName, const QString& errorMessage);
    
    // События от менеджера воркеров
    void onAllWorkersStarted();
    void onAllWorkersStopped();

private:
    // Инициализация
    void setupUI();
    void setupWorkers(std::unique_ptr<IDatabase> database);
    void setupTimers();
    void setupConnections();
    
    // Константы
    static constexpr unsigned int pauseBeforeLoad = 100;
    static constexpr int updatePeriod = 1000;
    
    // UI
    Ui::MainWindow *ui;
    
    // Бизнес-логика
    CounterManager m_counterManager;
    CountersModel m_countersModel;
    
    // Менеджер воркеров
    std::unique_ptr<IWorkerManager> m_workerManager;
    
    // Таймеры
    QTimer m_frequencyTimer;
    
    // Состояние
    double m_lastFrequency = 0;
    double m_lastTime = 0;
    qint64 m_lastSum = 0;
};

#endif // MAINWINDOW_H
