#pragma once

#include "Enums.h"

#include <QtCore>

#include <utility>

class BuildingBase : public QObject {
    Q_OBJECT
public:
    explicit BuildingBase(QObject* parent = nullptr);

    virtual QtCity::BuildingType getType() const = 0;
    virtual QtCity::ZoneType getCompatibleZone() const = 0;

    std::pair<int, int> getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getLevel();

    bool canBuildOnZone(const QtCity::ZoneType& zoneType) const;
    bool isBuildInProgress() const;
    void advanceBuildingProcess();
    bool canEvolveBuilding() const;
    void startEvolveBuilding();

signals:
    void buildingProcessFinished();

protected:
    virtual void evolveSpecificBuildingImpl() = 0;

protected:
    int m_Width;
    int m_Height;

    int m_BuildingProgress = 0;
    int m_BuildingLevel = 0;

private:
    static constexpr int s_FinishedBuildingValue = 128;
    static constexpr int s_MaxBuildingLevel = 3;
};
