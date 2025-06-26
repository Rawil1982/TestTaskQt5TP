#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/commands.h"
#include <QMessageBox>
#include <QDateTime>
#include <QHeaderView>

MainWindow::MainWindow(std::unique_ptr<IDatabase> database, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_database(std::move(database)),
      m_countersModel(m_counterManager, this) {

    ui->setupUi(this);

    // Настройка таблицы
    ui->tableView->setModel(&m_countersModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Настройка потоков
    setupWorkers();

    // Настройка команд
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addCounter);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeCounter);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveCounters);

    // Настройка таймеров
    setupTimers();

    // Инициализация времени
    m_lastTime = QDateTime::currentMSecsSinceEpoch();
    m_lastSum = m_counterManager.getSum();
}

MainWindow::~MainWindow() {
    if (m_incrementWorker) m_incrementWorker->stop();
    if (m_dbWorker) m_dbWorker->stop();
//   SaveCommand(countersModel, *dbWorker).execute(); //Не знаю надо или нет. Если надо, нужно блочить выход с мес. боксом.
}

void MainWindow::setupWorkers() {
    // Поток для работы с БД
    m_dbWorker = std::make_unique<DatabaseWorker>(std::move(m_database));
    connect(m_dbWorker.get(), &DatabaseWorker::countersLoaded,
            this, &MainWindow::onCountersLoaded);
    connect(m_dbWorker.get(), &DatabaseWorker::countersSaved,
            this, &MainWindow::onCountersSaved);
    m_dbWorker->start();

    // Задержка перед загрузкой, чтобы поток успел инициализироваться
    QTimer::singleShot(pauseBeforeLoad, [this]() {
        m_dbWorker->loadCounters();
    });

    // Поток для инкрементирования
    m_incrementWorker = std::make_unique<IncrementWorker>(m_counterManager);
    connect(m_incrementWorker.get(), &IncrementWorker::dataChanged,
            &m_countersModel, &CountersModel::refreshData);
    m_incrementWorker->start();
}

void MainWindow::setupTimers() {
    connect(&m_frequencyTimer, &QTimer::timeout, this, &MainWindow::updateFrequency);
    m_frequencyTimer.start(updatePeriod); // Обновление частоты 1 раз в секунду.
}

void MainWindow::addCounter() {
    m_countersModel.insertRow(m_countersModel.rowCount());
}

void MainWindow::removeCounter() {
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) return;

    // Сортируем в обратном порядке
    std::vector<int> rows;
    for (const auto& index : selected) {
        rows.push_back(index.row());
    }
    std::sort(rows.rbegin(), rows.rend());

    for (int row : rows) {
        m_countersModel.removeRow(row);
    }
}

void MainWindow::saveCounters() {
    SaveCommand(m_countersModel, *m_dbWorker).execute();
}

void MainWindow::updateFrequency() {
    double currentTime = QDateTime::currentMSecsSinceEpoch();
    double currentSum = m_counterManager.getSum();

    double timeDelta = (currentTime - m_lastTime) / updatePeriod;
    double sumDelta = currentSum - m_lastSum;

    double frequency = timeDelta > 0 ? sumDelta / timeDelta : m_lastFrequency;
    m_lastFrequency = frequency;
    ui->frequencyLabel->setText(
                tr("Частота: %1 итераций/сек").arg(frequency, 0, 'f', 2));

    m_lastTime = currentTime;
    m_lastSum = currentSum;
}

void MainWindow::onCountersLoaded(const std::vector<int>& counters) {
    m_countersModel.addCounters(counters);
    m_lastSum = m_counterManager.getSum();
}

void MainWindow::onCountersSaved() {
    QMessageBox::information(this, tr("Сохранение"), tr("Данные сохранены в БД"));
}
