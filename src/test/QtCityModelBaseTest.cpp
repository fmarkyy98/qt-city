#include "QtCityModelBaseTest.h"
#include "Enums.h"
#include "Factory.h"

void QtCityModelBaseTest::init()
{
	// Called before the first testfunction is executed
}

void QtCityModelBaseTest::test_FactoryConstValues()
{
	Factory factory;
	QCOMPARE(factory.getHeight(), 1);
	QCOMPARE(factory.getWidth(), 1);
	QCOMPARE(factory.getType(), qct::BuildingType::Factory);
	QCOMPARE(factory.getCompatibleZone(), qct::ZoneType::Industrial);
	QCOMPARE(factory.getHappynessFactor(), -2);
}

void QtCityModelBaseTest::test_FactoryWorkplace()
{
	Factory factory;
	QCOMPARE(factory.getWorkerCapacity(0), 0);
	QCOMPARE(factory.getWorkerCapacity(1), 300);
	QCOMPARE(factory.getWorkerCapacity(2), 600);
	QCOMPARE(factory.getWorkerCapacity(3), 1200);
}

void QtCityModelBaseTest::test_FactoryPossibilities()
{
	Factory factory;
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::Residential), false);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::Radioactive), false);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::Industrial), true);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::None), false);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::Service), false);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::All), true);
	QCOMPARE(factory.canBuildOnZone(qct::ZoneType::NotNone), true);
}

void QtCityModelBaseTest::cleanup()
{
	// Called after the last testfunction was executed
}