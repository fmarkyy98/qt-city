#include "ResidentialBuilding.h"

ResidentialBuilding::ResidentialBuilding(QObject* parent)
    : BuildingBase(parent)
{}


QtCity::BuildingType ResidentialBuilding::getType() const {
    return s_Type;
}

QtCity::ZoneType ResidentialBuilding::getCompatibleZone() const {
    return s_Zone;
}

int ResidentialBuilding::getChildInhabitantCount() const {
    return m_ChildInhabitantCount;
}

int ResidentialBuilding::getAdultInhabitantCount() const {
    return m_AdultInhabitantCount;
}

int ResidentialBuilding::getRetiredInhabitantCount() const {
    return m_RetiredInhabitantCount;
}

int ResidentialBuilding::getInhabitantCount() const {
    return m_ChildInhabitantCount + m_AdultInhabitantCount + m_RetiredInhabitantCount;
}

ResidentialBuilding& ResidentialBuilding::setChildInhabitantCount(int childCount) {
    if (childCount + m_AdultInhabitantCount + m_RetiredInhabitantCount > m_Capacity)
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_ChildInhabitantCount = childCount;

    return *this;
}

ResidentialBuilding& ResidentialBuilding::setAdultInhabitantCount(int adultCount) {
    if (m_ChildInhabitantCount + adultCount + m_RetiredInhabitantCount > m_Capacity)
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_AdultInhabitantCount = adultCount;

    return *this;
}

ResidentialBuilding& ResidentialBuilding::setRetiredInhabitantCount(int retiredCount) {
    if (m_ChildInhabitantCount + m_AdultInhabitantCount + retiredCount > m_Capacity)
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_RetiredInhabitantCount = retiredCount;

    return *this;
}

void ResidentialBuilding::settleIn(int childCount, int adultCount, int retiredCount) {
    if (getInhabitantCount() + childCount + adultCount + retiredCount > m_Capacity)
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_ChildInhabitantCount += childCount;
    m_AdultInhabitantCount += adultCount;
    m_RetiredInhabitantCount += retiredCount;
}

void ResidentialBuilding::removeInhabitant(int childCount, int adultCount, int retiredCount) {
    m_ChildInhabitantCount -= std::min(m_ChildInhabitantCount, childCount);
    m_AdultInhabitantCount -= std::min(m_AdultInhabitantCount, adultCount);
    m_RetiredInhabitantCount -= std::min(m_RetiredInhabitantCount, retiredCount);
}

void ResidentialBuilding::increseInhabitantAge() {
    int childrenToPromote = m_ChildInhabitantCount / 10;
    int adultsToPromote = m_AdultInhabitantCount / 10;
    int retiredsToPromote = m_RetiredInhabitantCount / 10;

    m_ChildInhabitantCount -= childrenToPromote;
    m_AdultInhabitantCount += childrenToPromote;

    m_AdultInhabitantCount -= adultsToPromote;
    m_RetiredInhabitantCount += adultsToPromote;

    m_RetiredInhabitantCount -= retiredsToPromote;
}

void ResidentialBuilding::evolveSpecificBuildingImpl() {
    m_Capacity = s_CapacityByLevel[m_BuildingLevel];
}
