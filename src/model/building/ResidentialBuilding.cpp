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

    auto serial = BuildingBase::serialize();
    dataList.insert(dataList.end(), serial.begin(), serial.end());

    return dataList;
}

void ResidentialBuilding::deserialize(std::list<int>& dataList) {
    m_ChildInhabitantCount = dataList.front(); dataList.pop_front();
    m_AdultInhabitantCount = dataList.front(); dataList.pop_front();
    m_RetiredInhabitantCount = dataList.front(); dataList.pop_front();

    BuildingBase::deserialize(dataList);
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

int ResidentialBuilding::getHappyness() const
{
    return _happyness;
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

ResidentialBuilding &ResidentialBuilding::setHappyness(int happyness)
{
    _happyness = happyness;

    return *this;
}

void ResidentialBuilding::settleIn(int childCount, int adultCount, int retiredCount) {
    int allToCome = childCount + adultCount + retiredCount;
    if (getInhabitantCount() + allToCome > getCapacity()) {
        double childRatio   = childCount   / static_cast<double>(allToCome);
        double adultRatio   = adultCount   / static_cast<double>(allToCome);
        double retiredRatio = retiredCount / static_cast<double>(allToCome);

        int freePlaces = getCapacity() - getInhabitantCount();
        childCount = freePlaces * childRatio;
        adultCount = freePlaces * adultRatio;
        retiredCount = freePlaces * retiredRatio;
    }


    m_ChildInhabitantCount += std::max(-m_ChildInhabitantCount, childCount);
    m_AdultInhabitantCount += std::max(-m_AdultInhabitantCount, adultCount);
    m_RetiredInhabitantCount += std::max(-m_RetiredInhabitantCount, retiredCount);
}

void ResidentialBuilding::removeInhabitant(int childCount, int adultCount, int retiredCount) {
    settleIn(-childCount, -adultCount, -retiredCount);
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
