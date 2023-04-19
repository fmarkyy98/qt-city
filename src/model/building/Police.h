#pragma once

#include "base/WorkplaceBase.h"

class Police : public WorkplaceBase {
    Q_OBJECT
public:
    explicit Police(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS
    DECLARE_BUILDING_BASE_MEMBERS
    DECLARE_WORKPLACE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Police;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::Service;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
    static constexpr int s_WorkerCapacityByLevel[] = {0, 20, 40, 80};
    static constexpr double s_ProfitByLevel[] = {0, -5, -6, -7};
};
