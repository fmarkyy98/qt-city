#pragma once

#include "IGameModel.h"
#include "GameModel.h"
#include "GameModelFactory.h"

#include <QtTest>

class QtCityGameModelTest: public QObject
{
    Q_OBJECT
public:
    QtCityGameModelTest() = default;
    virtual ~QtCityGameModelTest() = default;

private slots:
    void init();

    void test_getHeightReturnValue();

    void cleanup();
private:
    std::shared_ptr<IGameModel> m_pGameModel;
};
