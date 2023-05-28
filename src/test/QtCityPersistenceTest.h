#pragma once

#include "FileIOServiceFactory.h"
#include "IFileIOService.h"
#include "FileIOService.h"

#include <QtTest>

class QtCityPersistenceTest : public QObject
{
    Q_OBJECT
public:
    QtCityPersistenceTest() = default;
    virtual ~QtCityPersistenceTest() = default;

private slots:
    void init();

    void test_saveAndLoad();
    void test_SaveAndLoad_data();
    void test_Factory();
    void test_FactoryIsSingleton();
    void test_invalidPath();

    void cleanup();
private:
    std::shared_ptr<IFileIOService> m_pIFileIOService;
};