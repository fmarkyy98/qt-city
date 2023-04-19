#pragma once

#include "StructureBase.h"

#define DECLARE_BUILDING_BASE_MEMBERS              \
qct::ZoneType getCompatibleZone() const override;  \
std::pair<int, int> getSize() const override;      \
int getWidth() const override;                     \
int getHeight() const override;

#define DEFINE_BUILDING_BASE_MEMBERS(CLASS)       \
qct::ZoneType CLASS::getCompatibleZone() const {  \
    return s_Zone;                                \
}                                                 \
std::pair<int, int> CLASS::getSize() const {      \
    return {s_Width, s_Height};                   \
}                                                 \
int CLASS::getWidth() const {                     \
    return s_Width;                               \
}                                                 \
int CLASS::getHeight() const {                    \
    return s_Height;                              \
}

class BuildingBase : public StructureBase {
    Q_OBJECT
public:
    explicit BuildingBase(QObject* parent = nullptr);

    virtual qct::BuildingType getType() const = 0;

    virtual std::pair<int, int> getSize() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    int getLevel();

    bool canBuildOnZone(const qct::ZoneType& zoneType) const;
    bool isBuildInProgress() const;
    void advanceBuildingProcess();
    bool canEvolveBuilding() const;
    void startEvolveBuilding();

signals:
    void buildingProcessFinished();

protected:
    virtual qct::ZoneType getCompatibleZone() const = 0;

    virtual void evolveSpecificBuildingImpl();

protected:
    int m_BuildingProgress = 0;
    int m_BuildingLevel = 0;

private:
    static constexpr int s_FinishedBuildingValue = 128;
    static constexpr int s_MaxBuildingLevel = 3;
};
