#include "QtCityModelBaseTest.h"

#include "Enums.h"
#include "Factory.h"
#include "Forest.h"
#include "Police.h"
#include "ResidentialBuilding.h"
#include "Road.h"
#include "Stadium.h"
#include "Store.h"

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

void QtCityModelBaseTest::test_ForestValues()
{
	Forest forest;
	QCOMPARE(forest.getHeight(), 1);
	QCOMPARE(forest.getWidth(), 1);
	QCOMPARE(forest.getType(), qct::BuildingType::Forest);
	QCOMPARE(forest.getCompatibleZone(), qct::ZoneType::All);
	QCOMPARE(forest.getHappynessFactor(), 5);
}

void QtCityModelBaseTest::test_PoliceConstValues()
{
	Police police;
	QCOMPARE(police.getHeight(), 1);
	QCOMPARE(police.getWidth(), 1);
	QCOMPARE(police.getType(), qct::BuildingType::Police);
	QCOMPARE(police.getCompatibleZone(), qct::ZoneType::Service);
	QCOMPARE(police.getHappynessFactor(), 4);
}

void QtCityModelBaseTest::test_ResidentialBuildingConstValues()
{
	ResidentialBuilding residentialBuilding;
	QCOMPARE(residentialBuilding.getHeight(), 1);
	QCOMPARE(residentialBuilding.getWidth(), 1);
	QCOMPARE(residentialBuilding.getCapacity(3), 400);
	QCOMPARE(residentialBuilding.getCompatibleZone(), qct::ZoneType::Residential);
	QCOMPARE(residentialBuilding.getHappynessFactor(), 0);
	QCOMPARE(residentialBuilding.getAdultInhabitantCount(), 0);
	QCOMPARE(residentialBuilding.getRetiredInhabitantCount(), 0);
	QCOMPARE(residentialBuilding.getChildInhabitantCount(), 0);
}

void QtCityModelBaseTest::test_RoadConstValues()
{
	Road road;
	QCOMPARE(road.getHeight(), 1);
	QCOMPARE(road.getWidth(), 1);
	QCOMPARE(road.getType(), qct::BuildingType::Road);
	QCOMPARE(road.getCompatibleZone(), qct::ZoneType::All);
	QCOMPARE(road.getHappynessFactor(), 0);
}

void QtCityModelBaseTest::test_StadiumConstValues()
{
	Stadium stadium;
	QCOMPARE(stadium.getHeight(), 2);
	QCOMPARE(stadium.getWidth(), 2);
	QCOMPARE(stadium.getType(), qct::BuildingType::Stadium);
	QCOMPARE(stadium.getCompatibleZone(), qct::ZoneType::Service);
	QCOMPARE(stadium.getHappynessFactor(), 8);
}

void QtCityModelBaseTest::test_StoreConstValues()
{
	Store store;
	QCOMPARE(store.getHeight(), 1);
	QCOMPARE(store.getWidth(), 1);
	QCOMPARE(store.getType(), qct::BuildingType::Store);
	QCOMPARE(store.getCompatibleZone(), qct::ZoneType::Service);
	QCOMPARE(store.getHappynessFactor(), 0);
}

void QtCityModelBaseTest::cleanup()
{
	// Called after the last testfunction was executed
}