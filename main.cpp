#include "headers/mainwindow.h"

#include <QApplication>

#include "headers/databasefactory.h"
#include "headers/metatyperegistrator.h"
#include "headers/countermanager.h"
#include "headers/simpleincrementstrategy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MetatypeRegistrator::metatypeRegister();
    auto database = DatabaseFactory::createDatabase();
    auto counterManager = std::make_unique<CounterManager>(std::make_unique<SimpleIncrementStrategy>());
    MainWindow w(std::move(database), std::move(counterManager));
    w.show();

    return a.exec();
}
