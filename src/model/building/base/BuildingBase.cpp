#include "BuildingBase.h"

BuildingBase::BuildingBase(QObject *parent)
    : StructureBase(parent)
{}

std::list<int> BuildingBase::serialize() const {
    std::list<int> dataList;
    dataList.push_back(m_BuildingProgress);
    dataList.push_back(m_BuildingLevel);

    dataList.merge(StructureBase::serialize());

    return dataList;
}

void BuildingBase::deserialize(std::list<int>& dataList) {
    m_BuildingProgress = dataList.front(); dataList.pop_front();
    m_BuildingLevel = dataList.front(); dataList.pop_front();

    StructureBase::deserialize(dataList);
}

int BuildingBase::getLevel() const {
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
    if (m_BuildingLevel >= s_MaxBuildingLevel)
        throw std::invalid_argument("Building at max level.");

    m_BuildingProgress = 0;
}

void BuildingBase::evolveSpecificBuildingImpl() {}
