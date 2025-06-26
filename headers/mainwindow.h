#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QTimer>
#include "idatabase.h"
#include "countermanager.h"
#include "countersmodel.h"
#include "databaseworker.h"
#include "incrementworker.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::unique_ptr<IDatabase> m_database, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addCounter();
    void removeCounter();
    void saveCounters();
    void updateFrequency();
    void onCountersLoaded(const std::vector<int>& counters);
    void onCountersSaved();

private:
    const unsigned int pauseBeforeLoad = 100;
    void setupWorkers();
    void setupTimers();
    const int updatePeriod = 1000;
    double m_lastFrequency = 0;
    Ui::MainWindow *ui;
    CounterManager m_counterManager;
    std::unique_ptr<IDatabase> m_database;
    CountersModel m_countersModel;
    std::unique_ptr<DatabaseWorker> m_dbWorker;
    std::unique_ptr<IncrementWorker> m_incrementWorker;
    QTimer m_frequencyTimer;
    double m_lastTime = 0;
    qint64 m_lastSum = 0;
};

#endif // MAINWINDOW_H
