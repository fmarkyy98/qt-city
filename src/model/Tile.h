#pragma once

#include "building/base/BuildingBase.h"

struct Tile
{
    BuildingBase* building = nullptr;
    ZoneType zoneType = ZoneType::None;
};
