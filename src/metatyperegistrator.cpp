#include <QMetaType>
#include "../headers/metatyperegistrator.h"

void MetatypeRegistrator::metatypeRegister()
{
    qRegisterMetaType<std::vector<int>>("std::vector<int>");
}
