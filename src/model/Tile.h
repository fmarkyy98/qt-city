#pragma once

#include "building/base/BuildingBase.h"

class Tile
{
public:
    BuildingBase* getBuilding();
    ZoneType getZone();
private:
    BuildingBase* m_Building;
    ZoneType m_ZoneType;
};
