#include "GameModel.h"
#include "building/ResidentialBuilding.h"
#include "building/base/WorkplaceBase.h"

const QDate GameModel::m_dateAtStart = {1970, 1, 1};

GameModel::GameModel(std::shared_ptr<IFileIOService> fileIOService,
                     QObject *parent)
    : QObject(parent)
    , m_FileIOService(fileIOService)
    , m_Board(m_dateAtStart)
{}

void GameModel::save(const QString &path) const {
    std::list<int> dataList;

    dataList.merge(m_Board.serialize());
    dataList.push_back(m_money);

    m_FileIOService->save(path, dataList);
}

void GameModel::load(const QString &path) {
    std::list<int> dataList = m_FileIOService->load(path);

    m_Board.deserialize(dataList);
    m_money = dataList.front(); dataList.pop_front();
}

int GameModel::getHeight() const {
    return 25;
}

int GameModel::getWidth() const {
    return 15;
}

int GameModel::getCostOfPlacingZone() const {
    return m_costOfPlacingZone;
}

int GameModel::getCostOfBuildingBuilding() const {
    return m_costOfBuildingBuilding;
}

void GameModel::placeZone(qct::ZoneType zoneType, int row, int col) {
    if(m_money < m_costOfPlacingZone)
        throw std::invalid_argument("Not enough money left for Zone placement!");

    m_Board.placeZone(zoneType, {row,col});
    emit meta()->zonesChanged();
    emit meta()->boardChanged();
    m_money -= m_costOfPlacingZone;
    emit meta()->moneyChanged(m_money);
}

void GameModel::breakDownZone(int row, int col) {
    m_Board.breakDownZone({row,col});
    emit meta()->zonesChanged();
    m_money += m_costOfPlacingZone / 3;
    emit meta()->moneyChanged(m_money);
}

void GameModel::placeBuilding(qct::BuildingType buildingType, int row, int col) {
    if (m_money < m_costOfBuildingBuilding)
        throw std::invalid_argument("Not enough money left for Building construction!");

    m_Board.placeBuilding(buildingType, {row,col}, m_date);
    emit meta()->boardChanged();
    m_money -= m_costOfBuildingBuilding;
    emit meta()->moneyChanged(m_money);
}

qct::ZoneType GameModel::zoneAt(int row, int col) const {
    return m_Board.at({row, col}).zoneType;
}

const StructureBase* GameModel::structureAt(int row, int col) const {
    return m_Board.at({row, col}).structure;
}

void GameModel::newGame() {
    m_Board.reset(m_dateAtStart);
    emit meta()->boardChanged();
    m_money = m_moneyAtStart;
    emit meta()->moneyChanged(m_money);
    m_date = m_dateAtStart;
    emit meta()->dateChanged(m_date);
}

void GameModel::advanceSimulation() {
    auto buildings = m_Board.getBuildings();
    auto structures = m_Board.getStructures();

    advanceBuildingProcesses(buildings);
    distributeInhabitantsToWorkplaces(buildings);
    increaseMoney(buildings);
    buildOnRandomZone();
    m_date = m_date.addDays(1);
    emit meta()->dateChanged(m_date);
    if(m_date.daysInYear() == 1) {
        yearPassed(buildings);
        //forest bonus
    }
}

void GameModel::advanceBuildingProcesses(const std::vector<BuildingBase*>& buildings) {
    for (auto building : m_Board.getBuildings()) {
        if (building->isBuildInProgress()) {
            building->advanceBuildingProcess();
        }
    }
}

void GameModel::distributeInhabitantsToWorkplaces(const std::vector<BuildingBase *> &buildings) {
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

void GameModel::increaseMoney(const std::vector<BuildingBase *> &buildings) {
    for (auto building :buildings) {
        if (auto house = dynamic_cast<WorkplaceBase*>(building); house != nullptr) {
            m_money += house->calculateMoneyProduced();
        }
    }
}

void GameModel::buildOnRandomZone()
{
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            auto p = std::make_pair(j, i);
            if (static_cast<int>(m_Board.at(p).zoneType) & static_cast<int>(qct::ZoneType::NotNone) &&
                checkForRoad(p))
            {
                double randomValue= QRandomGenerator::global()->bounded(0, 100);
                if (randomValue < 10) {
                    auto buildings = getCompatibleBuildings(m_Board.at(p).zoneType);
                    int randomIndex = QRandomGenerator::global()->bounded(buildings.size());
                    auto randomElement = buildings[randomIndex];
                    placeBuilding(randomElement, j, i);
                }
            }
        }
    }
}

void GameModel::yearPassed(const std::vector<BuildingBase *> &buildings,
                           const std::vector<StructureBase *> &structures)
{
    maintainCity(buildings);
    maintainRoads(structures);
    increaseInhabitantAge(buildings);
}

void GameModel::maintainCity(const std::vector<BuildingBase *> &buildings)
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

void GameModel::maintainRoads(const std::vector<StructureBase *> &structures)
{
    int roadCount = 0;
    for (auto structure :structures) {
        ++roadCount;
    }
    m_money -= (roadCount * m_costOfMaintainingRoad);
}

void GameModel::increaseInhabitantAge(const std::vector<BuildingBase *> &buildings) {
    for (auto building :buildings) {
        if (auto house = dynamic_cast<ResidentialBuilding*>(building); house != nullptr) {
            house->increseInhabitantAge();
        }
    }
}

bool GameModel::checkForRoad(std::pair<int, int> position)
{
    auto [row, col] = position;
    bool hasNeighbouringRoad = false;

    if (row > 0) {
        auto above = m_Board.at(std::make_pair(row - 1, col)).structure;
        hasNeighbouringRoad |= above != nullptr && above->getType() == qct::BuildingType::Road;
    }
    if (row < getHeight() - 1) {
        auto below = m_Board.at(std::make_pair(row + 1, col)).structure;
        hasNeighbouringRoad |= below != nullptr && below->getType() == qct::BuildingType::Road;
    }
    if (col > 0) {
        auto left = m_Board.at(std::make_pair(row, col - 1)).structure;
        hasNeighbouringRoad |= left != nullptr && left->getType() == qct::BuildingType::Road;
    }
    if (col < getWidth() - 1) {
        auto right = m_Board.at(std::make_pair(row, col + 1)).structure;
        hasNeighbouringRoad |= right != nullptr && right->getType() == qct::BuildingType::Road;
    }

    return hasNeighbouringRoad;
}

bool GameModel::checkForForest(std::pair<int, int> position)
{
    auto [row, col] = position;
    bool hasForestNearThis = false;

    for (int i = std::max(0, col - 3); i <= std::min(getHeight(), col + 3); i++) {
            for (int j = std::max(0, row - 3); j <= std::min(getWidth(), row + 3); j++) {
                if (m_Board.at(std::make_pair(j, i)).structure->getType() == qct::BuildingType::Forest) {
                    if (std::abs(i - col) + std::abs(j - row) <= 3)
                        hasForestNearThis = true;
                }
            }
    }

    return hasForestNearThis;
}

int GameModel::calculateTax(std::pair<int, int> position)
{
    return 1;
}

QList<qct::BuildingType> GameModel::getCompatibleBuildings(qct::ZoneType zoneType)
{
    switch (zoneType) {
        case qct::ZoneType::Residential:
            return {qct::BuildingType::Residential};
        case qct::ZoneType::Service:
            return {qct::BuildingType::Store};
        case qct::ZoneType::Industrial:
            return {qct::BuildingType::Factory};
    }
    return {};
}
