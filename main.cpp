#include "headers/mainwindow.h"

#include <QApplication>

#include <headers/databasefactory.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto database = DatabaseFactory::createDatabase();
    MainWindow w(std::move(database));
    w.show();

    return a.exec();
}
