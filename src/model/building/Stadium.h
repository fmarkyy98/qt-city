#pragma once

#include "base/WorkplaceBase.h"

class Stadium : public WorkplaceBase {
public:
    explicit Stadium(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS
    DECLARE_BUILDING_BASE_MEMBERS
    DECLARE_WORKPLACE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Stadium;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::Service;
    static constexpr int s_Width = 2;
    static constexpr int s_Height = 2;
    static constexpr int s_WorkerCapacityByLevel[] = {0, 50, 50, 50};
    static constexpr double s_ProfitByLevel[] = {0, -30, -32, -35};
};
