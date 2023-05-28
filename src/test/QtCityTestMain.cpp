#include "QtCityGameModelTest.h"
#include "QtCityPersistenceTest.h"
#include "QtCityModelBaseTest.h"

int main(int argc, char* argv[])
{
    QtCityGameModelTest qtCityGameModelTest;
    QtCityPersistenceTest qtCityPersistenceTest;
    QtCityModelBaseTest qtCityModelBaseTest;

    // game model
    // QTest::qExec(&qtCityGameModelTest, argc, argv);
    // persistence
    QTest::qExec(&qtCityPersistenceTest, argc, argv);
    // game model
    //      base buildings:
    QTest::qExec(&qtCityModelBaseTest, argc, argv);

    return 0;
}
