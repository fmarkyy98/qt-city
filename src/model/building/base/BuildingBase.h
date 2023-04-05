#pragma once

#include <QObject>

#include "../../zone/ZoneType.h"

class BuildingBase : public QObject
{
    Q_OBJECT
public:
    explicit BuildingBase(QObject *parent = nullptr);

signals:
    void buildingProcessFinished();

public:
    virtual ZoneType getCompatibleZone() const = 0;

    std::pair<int, int> getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getLevel();

    bool canBuildOnZone(const ZoneType& zoneType) const;
    bool isBuildInProgress() const;
    void advanceBuildingProcess();
    bool canEvolveBuilding() const;
    void evolveBuilding();

protected:
    int m_width;
    int m_height;

    int m_buildingProgress = 0;
    int m_buildingLevel = 1;

private:
    static constexpr int s_finishedBuildingValue = 128;
    static constexpr int s_maxBuildingLevel = 3;
};
