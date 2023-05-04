#include "QtCityGameModelTest.h"

void QtCityGameModelTest::init()
{
    m_pGameModel = GameModelFactory::getGameModel();
}

void QtCityGameModelTest::test_getHeightReturnValue()
{
    int val = m_pGameModel->getHeight();
    QCOMPARE(val, 25);
}

void QtCityGameModelTest::cleanup()
{
    m_pGameModel.reset();
}

