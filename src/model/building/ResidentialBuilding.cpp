#include "ResidentialBuilding.h"

ResidentialBuilding::ResidentialBuilding(QObject* parent)
    : BuildingBase(parent)
{}

DEFINE_STRUCTURE_BASE_MEMBERS(ResidentialBuilding)
DEFINE_BUILDING_BASE_MEMBERS(ResidentialBuilding)

std::list<int> ResidentialBuilding::serialize() const {
    std::list<int> dataList;
    dataList.push_back(m_ChildInhabitantCount);
    dataList.push_back(m_AdultInhabitantCount);
    dataList.push_back(m_RetiredInhabitantCount);

    dataList.merge(BuildingBase::serialize());

    return dataList;
}

int ResidentialBuilding::getCapacity() const {
    return s_CapacityByLevel[m_BuildingLevel];
}

int ResidentialBuilding::getCapacity(int level) const {
    return s_CapacityByLevel[level];
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
