#include "GameModel.h"
#include "building/ResidentialBuilding.h"
#include "building/base/WorkplaceBase.h"

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
    if(m_money < m_costOfPlacingZone)
        throw std::invalid_argument("Not enough money left for Zone placement!");

    m_Board.placeZone(zoneType, {row,col});
    emit meta()->onZonesChanged();
    m_money -= m_costOfPlacingZone;
    emit meta()->onMoneyChanged(m_money);
}

void GameModel::breakDownZone(int row, int col)
{
    m_Board.breakDownZone({row,col});
    emit meta()->onZonesChanged();
    m_money += m_costOfBreakingZone / 3;
    emit meta()->onMoneyChanged(m_money);
}

void GameModel::placeBuilding(qct::BuildingType buildingType, int row, int col)
{
    if (m_money < m_costOfBuildingBuilding)
        throw std::invalid_argument("Not enough money left for Building construction!");

    m_Board.placeBuilding(buildingType, {row,col});
    emit meta()->onBoardChanged();
    m_money -= m_costOfBuildingBuilding;
    emit meta()->onMoneyChanged(m_money);
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
