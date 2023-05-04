#include "QtCityGameModelTest.h"

int main(int argc, char* argv[])
{
    QtCityGameModelTest qtCityGameModelTest;

    QTest::qExec(&qtCityGameModelTest, argc, argv);
    return 0;
}
