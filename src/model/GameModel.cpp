#include "GameModel.h"
#include "building/ResidentialBuilding.h"
#include "building/base/WorkplaceBase.h"
#include "QtCore/qdebug.h"

GameModel::GameModel(std::shared_ptr<IFileIOService> fileIOService,
                     QObject *parent)
    : QObject(parent)
    , m_FileIOService(fileIOService)
{}

void GameModel::save(const QString &path) const
{
    throw std::runtime_error("TODO/marko");
}

void GameModel::load(const QString &path)
{
    throw std::runtime_error("TODO/marko");
}

int GameModel::getHeight() const
{
    return 25;
}

int GameModel::getWidth() const
{
    return 15;
}

void GameModel::placeZone(qct::ZoneType zoneType, int row, int col)
{
    if(m_money >= m_costOfPlacingZone){
        m_Board.placeZone(zoneType, {row,col});
        emit meta()->onZonesChanged();
        m_money -= m_costOfPlacingZone;
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        throw std::invalid_argument("Not enough money left for Zone placement!");
    }
}

void GameModel::breakDownZone(int row, int col)
{
    if(m_money >= m_costOfBreakingZone){
        m_Board.breakDownZone({row,col});
        emit meta()->onZonesChanged();
        m_money -= m_costOfBreakingZone;
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        throw std::runtime_error("TODO");
    }
}

void GameModel::placeBuilding(qct::BuildingType buildingType, int row, int col)
{
    if (m_money >= m_costOfBuildingBuilding) {
        m_Board.placeBuilding(buildingType, {row,col});
        emit meta()->onBoardChanged();
        m_money -= m_costOfBuildingBuilding;
        emit meta()->onMoneyChanged(m_money);
    } else {
        throw std::invalid_argument("Not enough money left for Building construction!");
    }
}

qct::ZoneType GameModel::zoneAt(int row, int col) const
{
    return m_Board.at({row, col}).zoneType;
}

const StructureBase* GameModel::structureAt(int row, int col) const
{
    return m_Board.at({row, col}).structure;
}

void GameModel::newGame()
{
    m_Board.reset();
    m_money = m_moneyAtStart;
    emit meta()->onMoneyChanged(m_money);
}

void GameModel::advanceSimulation()
{
    auto buildings = m_Board.getBuildings();
    advanceBuildingProcesses(buildings);
    increaseInhabitantAge(buildings);
    distributeInhabitantsToWorkplaces(buildings);
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            //if(m_Board.at({row, col}).zoneType); //TODO
        }
    }
}

void GameModel::advanceBuildingProcesses(const std::vector<BuildingBase*>& buildings)
{
    for (auto building : m_Board.getBuildings()) {
        if (building->isBuildInProgress()) {
            building->advanceBuildingProcess();
        }
    }
}

void GameModel::increaseInhabitantAge(const std::vector<BuildingBase *> &buildings)
{
    for (auto building :buildings) {
        if (auto house = dynamic_cast<ResidentialBuilding*>(building); house != nullptr) {
            house->increseInhabitantAge();
        }
    }
}

void GameModel::distributeInhabitantsToWorkplaces(const std::vector<BuildingBase *> &buildings)
{
    int adultsSum = 0;
    int availableWorkplaceCount = 0;
    for (auto building : buildings) {
        if (auto house = dynamic_cast<ResidentialBuilding*>(building); house != nullptr) {
            adultsSum += house->getAdultInhabitantCount();
        }
        if (auto workplace = dynamic_cast<WorkplaceBase*>(building); workplace != nullptr) {
            availableWorkplaceCount += workplace->getWorkerCapacity();
        }
    }
    double workplaceLoadRatio = std::min(adultsSum / static_cast<double>(availableWorkplaceCount), 1.0);

    for (auto building : buildings) {
        if (auto workplace = dynamic_cast<WorkplaceBase*>(building); workplace != nullptr) {
            workplace->setWorkerCount(workplace->getWorkerCapacity() * workplaceLoadRatio);
        }
    }
}

void GameModel::increaseMoney(const std::vector<BuildingBase *> &buildings)
{
    for (auto building :buildings) {
        if (auto house = dynamic_cast<WorkplaceBase*>(building); house != nullptr) {
            m_money += house->calculateMoneyProduced();
        }
    }
}

void GameModel::yearPassed(const std::vector<BuildingBase *> &buildings)
{
    int stadiumCount = 0;
    int policeCount = 0;
    for (auto building :buildings) {
        switch (building->getType()) {
        case qct::BuildingType::Stadium:
            ++stadiumCount;
            break;
        case qct::BuildingType::Police:
            ++policeCount;
            break;
        }
    }
    m_money -= (stadiumCount * m_costOfMaintainingStadium + policeCount * m_costOfMaintainingPolice);
}
