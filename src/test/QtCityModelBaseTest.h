#pragma once

#include "BuildingBase.h"
#include "StructureBase.h"
#include "WorkplaceBase.h"

#include <QtTest>

class QtCityModelBaseTest : public QObject
{
	Q_OBJECT

public:
	QtCityModelBaseTest() = default;
	virtual ~QtCityModelBaseTest() = default;

private slots:
	void init();

	//factory
	void test_FactoryConstValues();
	void test_FactoryWorkplace();
	void test_FactoryPossibilities();
	//Forest
	void test_ForestValues();
	//Police
	void test_PoliceConstValues();

	void cleanup();
private:

};