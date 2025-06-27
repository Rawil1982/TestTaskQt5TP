#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <thread>
#include "domain/entities/counter.h"

namespace {
    constexpr int WINDOW_WIDTH = 600;
    constexpr int WINDOW_HEIGHT = 400;
    constexpr int UPDATE_INTERVAL_MS = 1000;
    constexpr int ID_COLUMN_INDEX = 0;
}

MainWindow::MainWindow(std::shared_ptr<CountersViewModel> viewModel, 
                     std::unique_ptr<IncrementWorker> worker,
                     QWidget* parent)
    : QMainWindow(parent), m_viewModel(viewModel), m_worker(std::move(worker)) {
    setupUI();
    setupConnections();
    
    // Запускаем воркер в отдельном потоке
    if (m_worker) {
        m_workerThread = std::make_unique<std::thread>([this]() {
            m_worker->start();
        });
    }
    
    // Запускаем таймер обновления
    m_updateTimer->start(UPDATE_INTERVAL_MS);
}

MainWindow::~MainWindow() {
    if (m_worker) {
        m_worker->stop();
    }
    
    // Ждем завершения потока
    if (m_workerThread && m_workerThread->joinable()) {
        m_workerThread->join();
    }
}

void MainWindow::setupUI() {
    // Устанавливаем значания для юай
    setWindowTitle(tr("Счетчики"));
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // Таблица
    m_tableView = new QTableView(this);
    m_tableModel = new CountersTableModel(this);
    m_tableView->setModel(m_tableModel);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    
    // Скрываем колонку ID
    m_tableView->hideColumn(ID_COLUMN_INDEX);
    
    mainLayout->addWidget(m_tableView);
    
    // Лейбл частоты
    m_frequencyLabel = new QLabel(tr("Частота: 0.00 счетчиков/сек"), this);
    mainLayout->addWidget(m_frequencyLabel);
    
    // Кнопки и лэйауты
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    m_addButton = new QPushButton(tr("Добавить"), this);
    buttonLayout->addWidget(m_addButton);
    
    m_removeButton = new QPushButton(tr("Удалить"), this);
    buttonLayout->addWidget(m_removeButton);
    
    m_saveButton = new QPushButton(tr("Сохранить"), this);
    buttonLayout->addWidget(m_saveButton);
    
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    
    // Таймер обновления
    m_updateTimer = new QTimer(this);
}

void MainWindow::setupConnections() {
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    
    if (m_viewModel) {
        connect(m_viewModel.get(), &CountersViewModel::countersChanged, this, &MainWindow::onCountersChanged);
        connect(m_viewModel.get(), &CountersViewModel::frequencyChanged, this, &MainWindow::onFrequencyChanged);
    }
    
    connect(m_updateTimer, &QTimer::timeout, this, &MainWindow::updateTable);
}

void MainWindow::onAddButtonClicked() {
    if (m_viewModel) {
        m_viewModel->addCounter();
    }
}

void MainWindow::onRemoveButtonClicked() {
    const QModelIndex currentIndex = m_tableView->currentIndex();
    if (currentIndex.isValid() && m_viewModel) {
        m_viewModel->removeCounter(currentIndex.row());
    }
}

void MainWindow::onSaveButtonClicked() {
    if (m_viewModel) {
        m_viewModel->saveCounters();
        QMessageBox::information(this, tr("Успех"), tr("Счетчики сохранены"));
    }
}

void MainWindow::onCountersChanged() {
    updateTable();
}

void MainWindow::onFrequencyChanged() {
    if (m_viewModel) {
        m_frequencyLabel->setText(m_viewModel->getFrequencyText());
    }
}

void MainWindow::updateTable() {
    if (m_viewModel) {
        m_viewModel->updateFrequency();
        
        const auto counters = m_viewModel->getCounterValues();
        QVector<Counter> counterObjects;
        counterObjects.reserve(counters.size());
        for (size_t i = 0; i < counters.size(); ++i) {
            counterObjects.append(Counter(static_cast<int>(i + 1), counters[i]));
        }
        m_tableModel->setCounters(counterObjects);
    }
} 
