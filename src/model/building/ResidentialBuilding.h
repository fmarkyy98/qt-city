#pragma once

#include "base/BuildingBase.h"

#include <QObject>

class ResidentialBuilding : public BuildingBase {
    Q_OBJECT
public:
    ResidentialBuilding(QObject* parent = nullptr);

    QtCity::BuildingType getType() const override;
    QtCity::ZoneType getCompatibleZone() const override;

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
    int m_Capacity = s_CapacityByLevel[m_BuildingLevel];
    int m_ChildInhabitantCount = 0;
    int m_AdultInhabitantCount = 0;
    int m_RetiredInhabitantCount = 0;

private:
    static constexpr QtCity::BuildingType s_Type = QtCity::BuildingType::Residential;
    static constexpr QtCity::ZoneType s_Zone = QtCity::ZoneType::Residential;
    static constexpr int s_CapacityByLevel[] = {0, 100, 200, 400};
};

