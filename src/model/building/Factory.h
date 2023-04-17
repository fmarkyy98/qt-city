#pragma once

#include <QObject>

#include "base/WorkplaceBase.h"

class Factory : public WorkplaceBase {
    Q_OBJECT
public:
    Factory(QObject* parent = nullptr);

    BuildingType getType() const override;
    ZoneType getCompatibleZone() const override;

    std::pair<int, int> getSize() const override;
    int getWidth() const override;
    int getHeight() const override;

    int getWorkerCapacity() const override;
    double getProfitAfterWorker() const override;

protected:
    void evolveSpecificBuildingImpl() override;

private:
    static constexpr BuildingType s_Type = BuildingType::Factory;
    static constexpr ZoneType s_Zone = ZoneType::Industrial;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
    static constexpr int s_WorkerCapacityByLevel[] = {0, 300, 600, 1200};
    static constexpr double s_ProfitByLevel[] = {0, 0.8, 1, 1.2};
};

