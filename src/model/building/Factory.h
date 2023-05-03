#pragma once

#include "base/WorkplaceBase.h"

class Factory : public WorkplaceBase {
    Q_OBJECT
public:
    explicit Factory(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS
    DECLARE_BUILDING_BASE_MEMBERS
    DECLARE_WORKPLACE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Factory;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::Industrial;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
    static constexpr int s_WorkerCapacityByLevel[] = {0, 300, 600, 1200};
    static constexpr double s_ProfitByLevel[] = {0, 0.8, 1, 1.2};

public:
    static constexpr int workerCapacity = s_WorkerCapacityByLevel[1];
};
