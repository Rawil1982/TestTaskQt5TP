#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/commands/savecommand.h"
#include "headers/interfaces/idatabase.h"
#include "headers/databaseworker.h"
#include "headers/countermanager.h"
#include "headers/countersmodel.h"
#include "headers/workermanager.h"
#include "headers/simpleincrementstrategy.h"
#include "headers/frequencyupdater.h"
#include <QMessageBox>
#include <QDateTime>
#include <QHeaderView>
#include <QDebug>
#include <QTimer>
#include <algorithm>
#include <QModelIndexList>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QHeaderView>
#include <QTableView>
#include <QLabel>
#include <QModelIndex>
#include <QModelIndexList>

MainWindow::MainWindow(std::unique_ptr<IDatabase> database, std::unique_ptr<CounterManager> counterManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_counterManager(std::move(counterManager)),
      m_countersModel(std::make_unique<CountersModel>(*m_counterManager, this)),
      m_frequencyUpdater(std::make_unique<FrequencyUpdater>(*m_counterManager, updatePeriod))
{
    ui->setupUi(this);
    
    setupUI();
    setupWorkers(std::move(database));
    setupTimers();
    setupConnections();

    m_lastTime = QDateTime::currentMSecsSinceEpoch();
    m_lastSum = m_counterManager->getSum();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    ui->tableView->setModel(m_countersModel.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupWorkers(std::unique_ptr<IDatabase> database) {
    m_workerManager = std::make_unique<WorkerManager>(*m_counterManager, std::move(database));
    
    connect(m_workerManager.get(), &IWorkerManager::allWorkersStarted,
            this, &MainWindow::onAllWorkersStarted);
    connect(m_workerManager.get(), &IWorkerManager::allWorkersStopped,
            this, &MainWindow::onAllWorkersStopped);
    connect(m_workerManager.get(), &IWorkerManager::workerError,
            this, &MainWindow::onWorkerError);
    
    auto dbWorker = dynamic_cast<DatabaseWorker*>(m_workerManager->getDatabaseWorker());
    if (dbWorker) {
        connect(dbWorker, &DatabaseWorker::countersLoaded,
                this, &MainWindow::onCountersLoaded);
        connect(dbWorker, &DatabaseWorker::countersSaved,
                this, &MainWindow::onCountersSaved);
    }
    
    auto incWorker = m_workerManager->getIncrementWorker();
    if (incWorker) {
        connect(incWorker, &IWorker::dataChanged,
                m_countersModel.get(), &CountersModel::refreshData);
    }
    
    m_workerManager->startAll();
    
    QTimer::singleShot(pauseBeforeLoad, [this]() {
        auto dbWorker = dynamic_cast<DatabaseWorker*>(m_workerManager->getDatabaseWorker());
        if (dbWorker) {
            dbWorker->loadCounters();
        }
    });
}

void MainWindow::setupTimers() {
    connect(&m_frequencyTimer, &QTimer::timeout, this, &MainWindow::updateFrequency);
    m_frequencyTimer.start(updatePeriod);
}

void MainWindow::setupConnections() {
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addCounter);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeCounter);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveCounters);
}

void MainWindow::addCounter() {
    m_countersModel->insertRow(m_countersModel->rowCount());
}

void MainWindow::removeCounter() {
    const QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) return;

    std::vector<int> rows;
    for (const auto& index : selected) {
        rows.push_back(index.row());
    }
    std::sort(rows.rbegin(), rows.rend());

    for (int row : rows) {
        m_countersModel->removeRow(row);
    }
}

void MainWindow::saveCounters() {
    auto dbWorker = dynamic_cast<DatabaseWorker*>(m_workerManager->getDatabaseWorker());
    if (dbWorker) {
        SaveCommand(*m_countersModel, *dbWorker).execute();
    }
}

void MainWindow::onCountersLoaded(const std::vector<int>& counters) {
    m_countersModel->addCounters(counters);
    m_lastSum = m_counterManager->getSum();
}

void MainWindow::onCountersSaved() {
    QMessageBox::information(this, tr("Сохранение"), tr("Данные сохранены в БД"));
}

void MainWindow::onWorkerError(const QString& workerName, const QString& errorMessage) {
    QMessageBox::warning(this, tr("Worker error:"),
                         tr(" [%1]: %2").arg(workerName, errorMessage));
}

void MainWindow::onAllWorkersStarted() {
    qDebug() << "All workers started successfully";
}

void MainWindow::onAllWorkersStopped() {
    qDebug() << "All workers stopped";
}

void MainWindow::updateFrequency()
{
    ui->frequencyLabel->setText(tr("Частота: %1 итераций/сек")
                                .arg(m_frequencyUpdater->updateFrequency(), 0, 'f', 2));
}
