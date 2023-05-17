#pragma once

#include "base/WorkplaceBase.h"

class Store : public WorkplaceBase {
    Q_OBJECT
public:
    explicit Store(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS
    DECLARE_BUILDING_BASE_MEMBERS
    DECLARE_WORKPLACE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Store;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::Service;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
    static constexpr int s_WorkerCapacityByLevel[] = {0, 50, 100, 200};
    static constexpr double s_ProfitByLevel[] = {0, -0.8, -1, -1.2};
    static constexpr double s_HappynessFactor = 0;

public:
    static constexpr int workerCapacity = s_WorkerCapacityByLevel[1];
};
