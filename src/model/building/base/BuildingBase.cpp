#include "BuildingBase.h"

using namespace model;

BuildingBase::BuildingBase(QObject *parent)
    : QObject(parent)
{}

std::pair<int, int> BuildingBase::getSize() const {
    return {m_width, m_height};
}

int BuildingBase::getWidth() const {
    return m_width;
}

int BuildingBase::getHeight() const {
    return m_height;
}

int BuildingBase::getLevel() {
    return m_buildingLevel;
}

bool BuildingBase::canBuildOnZone(const ZoneType& zoneType) const {
    return zoneType == getCompatibleZone();
}

bool BuildingBase::isBuildInProgress() const {
    return m_buildingProgress < s_finishedBuildingValue;
}

void BuildingBase::advanceBuildingProcess() {
    m_buildingProgress += 16 / (m_width * m_height);

    if (m_buildingProgress > s_finishedBuildingValue)
        emit buildingProcessFinished();
}

bool BuildingBase::canEvolvBuilding() const {
    return m_buildingLevel < s_maxBuildingLevel;
}

void BuildingBase::evolvBuilding() {
    ++m_buildingLevel;
    m_buildingProgress = 0;
}

