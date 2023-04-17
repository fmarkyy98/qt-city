#include "ResidentialBuilding.h"

ResidentialBuilding::ResidentialBuilding(QObject* parent)
    : BuildingBase(parent)
{}


BuildingType ResidentialBuilding::getType() const {
    return s_Type;
}

ZoneType ResidentialBuilding::getCompatibleZone() const {
    return s_Zone;
}

std::pair<int, int> ResidentialBuilding::getSize() const {
    return {s_Width, s_Height};
}

int ResidentialBuilding::getWidth() const {
    return s_Width;
}

int ResidentialBuilding::getHeight() const {
    return s_Height;
}

int ResidentialBuilding::getCapacity() const {
    return s_CapacityByLevel[m_BuildingLevel];
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
    if (childCount + m_AdultInhabitantCount + m_RetiredInhabitantCount > getCapacity())
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_ChildInhabitantCount = childCount;

    return *this;
}

ResidentialBuilding& ResidentialBuilding::setAdultInhabitantCount(int adultCount) {
    if (m_ChildInhabitantCount + adultCount + m_RetiredInhabitantCount > getCapacity())
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_AdultInhabitantCount = adultCount;

    return *this;
}

ResidentialBuilding& ResidentialBuilding::setRetiredInhabitantCount(int retiredCount) {
    if (m_ChildInhabitantCount + m_AdultInhabitantCount + retiredCount > getCapacity())
        throw std::invalid_argument("Inhabitant limit exceeded :(");

    m_RetiredInhabitantCount = retiredCount;

    return *this;
}

void ResidentialBuilding::settleIn(int childCount, int adultCount, int retiredCount) {
    if (getInhabitantCount() + childCount + adultCount + retiredCount > getCapacity())
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
    // TODO do we need this?
}
