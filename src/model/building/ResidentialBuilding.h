#pragma once

#include "base/BuildingBase.h"

class ResidentialBuilding : public BuildingBase {
    Q_OBJECT
public:
    ResidentialBuilding(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS
    DECLARE_BUILDING_BASE_MEMBERS
    std::list<int> serialize() const final;
    void deserialize(std::list<int>& dataList) final;

    int getCapacity() const;
    int getCapacity(int level) const;

    int getChildInhabitantCount() const;
    int getAdultInhabitantCount() const;
    int getRetiredInhabitantCount() const;
    int getInhabitantCount() const;

    ResidentialBuilding& setChildInhabitantCount(int childCount);
    ResidentialBuilding& setAdultInhabitantCount(int adultCount);
    ResidentialBuilding& setRetiredInhabitantCount(int retiredCount);

    void settleIn(int childCount, int adultCount, int retiredCount);
    void removeInhabitant(int childCount, int adultCount, int retiredCount);
    void increseInhabitantAge();

protected:
    void evolveSpecificBuildingImpl() override;

private:
    int m_ChildInhabitantCount = 0;
    int m_AdultInhabitantCount = 0;
    int m_RetiredInhabitantCount = 0;

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Residential;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::Residential;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
    static constexpr int s_CapacityByLevel[] = {0, 100, 200, 400};

public:
    static constexpr int capacity = s_CapacityByLevel[1];
};

