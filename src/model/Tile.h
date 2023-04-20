#pragma once

#include "building/base/BuildingBase.h"

struct Tile
{
    StructureBase* structure = nullptr;
    qct::ZoneType zoneType = qct::ZoneType::None;
};
