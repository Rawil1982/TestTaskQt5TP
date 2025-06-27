#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <memory>

#include "../rawil_gui/presentation/views/mainwindow.h"
#include "../rawil_core/infrastructure/database/sqlitedatabase.h"
#include "../rawil_core/domain/repositories/counterrepository.h"
#include "../rawil_core/domain/services/counterservice.h"
#include "../rawil_core/domain/services/frequencycalculator.h"
#include "../rawil_core/infrastructure/workers/incrementworker.h"
#include "../rawil_gui/presentation/viewmodels/countersviewmodel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Создаем путь к базе данных
    QString databasePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(databasePath);
    databasePath += "/counters.db";
    
    // Создаем зависимости
    auto database = std::make_shared<SQLiteDatabase>(databasePath);
    auto repository = std::make_shared<CounterRepository>(database);
    auto frequencyCalculator = std::make_unique<FrequencyCalculator>();
    
    auto counterService = std::make_shared<CounterService>(repository, std::move(frequencyCalculator));
    auto viewModel = std::make_shared<CountersViewModel>(counterService);
    auto incrementWorker = std::make_unique<IncrementWorker>(repository);
    
    // Создаем и показываем главное окно
    MainWindow window(viewModel, std::move(incrementWorker));
    window.show();
    
    return app.exec();
} 