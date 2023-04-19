#pragma once

#include "building/base/BuildingBase.h"

struct Tile
{
    BuildingBase* building = nullptr;
    qct::ZoneType zoneType = qct::ZoneType::None;
};
