#pragma once

#include "StructureBase.h"

#define DECLARE_BUILDING_BASE_MEMBERS
#define DEFINE_BUILDING_BASE_MEMBERS(CLASS)

class BuildingBase : public StructureBase {
    Q_OBJECT
public:
    explicit BuildingBase(QObject* parent = nullptr);
    int getLevel() const;

    bool isBuildInProgress() const;
    void advanceBuildingProcess();
    bool canEvolveBuilding() const;
    void startEvolveBuilding();

signals:
    void buildingProcessFinished();

protected:
    virtual void evolveSpecificBuildingImpl();

protected:
    int m_BuildingProgress = 0;
    int m_BuildingLevel = 0;

private:
    static constexpr int s_FinishedBuildingValue = 128;
    static constexpr int s_MaxBuildingLevel = 3;
};
