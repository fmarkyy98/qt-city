#include "QtCityPersistenceTest.h"

#include <QtCore/qdebug.h>
#include <QtCore/qstringlist.h>

void QtCityPersistenceTest::init()
{
	m_pIFileIOService = FileIOServiceFactory::getFileIOService();
}

void QtCityPersistenceTest::test_saveAndLoad()
{
	std::list<int> dataList = { 1, 2, 3, 4, 5 };
	m_pIFileIOService->save("test.txt", dataList);

	std::list<int> loadedDataList = m_pIFileIOService->load("test.txt");
	QCOMPARE(dataList, loadedDataList);
}

void QtCityPersistenceTest::test_SaveAndLoad_data()
{
	std::list<int> emptyList = {};
	std::list<int> singleDataList = { 42 };
	std::list<int> multipleDataList = {};
	for (int i = 1; i <= 1000; ++i)
	{
		multipleDataList.push_back(i);
	}

	m_pIFileIOService->save("empty.txt", emptyList);
	m_pIFileIOService->save("single.txt", singleDataList);
	m_pIFileIOService->save("multiple.txt", multipleDataList);

	QCOMPARE(m_pIFileIOService->load("empty.txt"), emptyList);
	QCOMPARE(m_pIFileIOService->load("single.txt"), singleDataList);
	QCOMPARE(m_pIFileIOService->load("multiple.txt"), multipleDataList);
}

void QtCityPersistenceTest::test_Factory()
{
	std::shared_ptr<IFileIOService> pIFileIOService = FileIOServiceFactory::getFileIOService();
	QVERIFY(pIFileIOService != nullptr);
}

void QtCityPersistenceTest::test_FactoryIsSingleton()
{
	std::shared_ptr<IFileIOService> pIFileIOService1 = FileIOServiceFactory::getFileIOService();
	std::shared_ptr<IFileIOService> pIFileIOService2 = FileIOServiceFactory::getFileIOService();
	QVERIFY(pIFileIOService1 == pIFileIOService2);
	QCOMPARE(pIFileIOService1.use_count(), 4);
	pIFileIOService1.reset();
	QCOMPARE(pIFileIOService2.use_count(), 3);
}

void QtCityPersistenceTest::test_invalidPath()
{
	std::list<int> dataList = { 1, 2, 3, 4, 5 };
	m_pIFileIOService->save("test.txt", dataList);

	std::list<int> loadedDataList = m_pIFileIOService->load("invalid.txt");

	QCOMPARE(loadedDataList, std::list<int>());
}

void QtCityPersistenceTest::cleanup()
{
	m_pIFileIOService.reset();
}