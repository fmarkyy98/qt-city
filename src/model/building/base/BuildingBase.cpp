#include "BuildingBase.h"

BuildingBase::BuildingBase(QObject *parent)
    : QObject(parent)
{}

std::pair<int, int> BuildingBase::getSize() const {
    return {m_Width, m_Height};
}

int BuildingBase::getWidth() const {
    return m_Width;
}

int BuildingBase::getHeight() const {
    return m_Height;
}

int BuildingBase::getLevel() {
    return m_BuildingLevel;
}

bool BuildingBase::canBuildOnZone(const QtCity::ZoneType& zoneType) const {
    return zoneType == getCompatibleZone();
}

bool BuildingBase::isBuildInProgress() const {
    return m_BuildingProgress < s_FinishedBuildingValue;
}

void BuildingBase::advanceBuildingProcess() {
    m_BuildingProgress += 16 / (m_Width * m_Height);

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

