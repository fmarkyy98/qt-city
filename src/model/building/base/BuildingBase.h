#pragma once

#include <QObject>

#include "../../../common/building/BuildingType.h"
#include "../../../common/zone/ZoneType.h"

class BuildingBase : public QObject {
    Q_OBJECT
public:
    explicit BuildingBase(QObject* parent = nullptr);

    virtual BuildingType getType() const = 0;

    virtual std::pair<int, int> getSize() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    int getLevel();

    bool canBuildOnZone(const ZoneType& zoneType) const;
    bool isBuildInProgress() const;
    void advanceBuildingProcess();
    bool canEvolveBuilding() const;
    void startEvolveBuilding();

signals:
    void buildingProcessFinished();

protected:
    virtual ZoneType getCompatibleZone() const = 0;

    virtual void evolveSpecificBuildingImpl() = 0;

protected:
    int m_BuildingProgress = 0;
    int m_BuildingLevel = 0;

private:
    static constexpr int s_FinishedBuildingValue = 128;
    static constexpr int s_MaxBuildingLevel = 3;
};
