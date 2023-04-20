#include "BuildingBase.h"

BuildingBase::BuildingBase(QObject *parent)
    : StructureBase(parent)
{}

int BuildingBase::getLevel() {
    return m_BuildingLevel;
}

bool BuildingBase::isBuildInProgress() const {
    return m_BuildingProgress < s_FinishedBuildingValue;
}

void BuildingBase::advanceBuildingProcess() {
    m_BuildingProgress += 16 / (getWidth() * getHeight());

    if (m_BuildingProgress > s_FinishedBuildingValue) {
        ++m_BuildingLevel;
        evolveSpecificBuildingImpl();
        emit buildingProcessFinished();
    }
}

bool BuildingBase::canEvolveBuilding() const {
    return m_BuildingLevel < s_MaxBuildingLevel;
}

void BuildingBase::startEvolveBuilding() {
    m_BuildingProgress = 0;
}

void BuildingBase::evolveSpecificBuildingImpl() {}
