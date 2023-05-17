#include "GameModel.h"
#include "building/ResidentialBuilding.h"
#include "building/Forest.h"
#include "building/base/WorkplaceBase.h"

const QDate GameModel::m_dateAtStart = {1970, 1, 1};

GameModel::GameModel(std::shared_ptr<IFileIOService> fileIOService,
                     QObject *parent)
    : QObject(parent)
    , m_FileIOService(fileIOService)
    , m_Board(m_dateAtStart)
{
    connect(&m_Board,
            &GameBoard::buildingProcessFinished,
            meta(),
            &GameModel::Meta::boardChanged);
}

void GameModel::save(const QString &path) const {
    std::list<int> dataList;

    dataList.push_back(m_money);
    dataList.push_back(m_date.year());
    dataList.push_back(m_date.month());
    dataList.push_back(m_date.day());

    auto serial = m_Board.serialize();
    dataList.insert(dataList.end(), serial.begin(), serial.end());

    m_FileIOService->save(path, dataList);
}

void GameModel::load(const QString &path) {
    std::list<int> dataList = m_FileIOService->load(path);

    m_money = dataList.front(); dataList.pop_front();
    int y = dataList.front(); dataList.pop_front();
    int m = dataList.front(); dataList.pop_front();
    int d = dataList.front(); dataList.pop_front();
    m_date = {y, m, d};

    m_Board.reset(m_date);
    m_Board.deserialize(dataList);

    qDebug() << "[SIZE]" << dataList.size();
    qDebug() << "[SIZE]" << dataList.empty();
    assert(dataList.empty() && "Deserialization item number missmatch.");
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

int GameModel::getGlobalInhabitantCount() const {
    auto buildings = m_Board.getBuildings();
    return std::accumulate(buildings.begin(), buildings.end(),
                           0,
                           [](int accumulated, BuildingBase* building) {
                               auto house = dynamic_cast<ResidentialBuilding*>(building);
                               if (house == nullptr)
                                   return accumulated;

                               return accumulated + house->getInhabitantCount();
                           });
}

int GameModel::getGlobalInhabitantCapacity() const {
    auto buildings = m_Board.getBuildings();
    return std::accumulate(buildings.begin(), buildings.end(),
                           0,
                           [](int accumulated, BuildingBase* building) {
                               auto house = dynamic_cast<ResidentialBuilding*>(building);
                               if (house == nullptr)
                                   return accumulated;

                               return accumulated + house->getCapacity();
                           });
}

int GameModel::getGlobalWorkerCount() const {
    auto buildings = m_Board.getBuildings();
    return std::accumulate(buildings.begin(), buildings.end(),
                           0,
                           [](int accumulated, BuildingBase* building) {
                               auto workplace = dynamic_cast<WorkplaceBase*>(building);
                               if (workplace == nullptr)
                                   return accumulated;

                               return accumulated + workplace->getWorkerCount();
                           });
}

int GameModel::getGlobalWorkerCapacity() const {
    auto buildings = m_Board.getBuildings();
    return std::accumulate(buildings.begin(), buildings.end(),
                           0,
                           [](int accumulated, BuildingBase* building) {
                               auto workplace = dynamic_cast<WorkplaceBase*>(building);
                               if (workplace == nullptr)
                                   return accumulated;

                               return accumulated + workplace->getWorkerCapacity();
                           });
}

int GameModel::getGlobalHappyness() const {
    auto buildings = m_Board.getBuildings();
    auto [sumHappyness, houseCount]
        = std::accumulate(buildings.begin(), buildings.end(),
                          std::pair{0, 0},
                          [](std::pair<int, int> accumulated, BuildingBase* building) {
                              if (auto house = dynamic_cast<ResidentialBuilding*>(building);
                                  house != nullptr) {
                                  accumulated.first += house->getCapacity();
                                  ++accumulated.second;
                              }

                              return accumulated;
                          });

    return sumHappyness / houseCount;
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

void GameModel::evolveBuilding(int row, int col)
{
    m_Board.evolveBuilding({row,col});
    emit meta()->boardChanged();
}

void GameModel::demolishBuilding(int row, int col)
{
    m_Board.demolishBuilding({row,col});
    emit meta()->boardChanged();
}

qct::ZoneType GameModel::zoneAt(int row, int col) const {
    return m_Board.at({row, col}).zoneType;
}

const StructureBase* GameModel::structureAt(int row, int col) const {
    return m_Board.at({row, col}).structure;
}

void GameModel::newGame() {
    m_Board.reset(m_dateAtStart);
    m_Board.randomForestPlacement(m_dateAtStart);
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
    calculateHappyness();
    settleInPeople();

    m_date = m_date.addDays(1);
    emit meta()->dateChanged(m_date);

    double randomValue = QRandomGenerator::global()->bounded(0, 100);
    if (randomValue < 2)
        catastrophe();

    if(m_date.daysInYear() == 1) {
        yearPassed(buildings, structures);
    }
}

void GameModel::yearPassed(const std::vector<BuildingBase *> &buildings,
                           const std::vector<StructureBase *> &structures)
{
    maintainCity(buildings);
    maintainRoads(structures);
    maintainForests(structures);
    increaseInhabitantAge(buildings);
    calculateTax(buildings);
    calculatePension(buildings);
    calculateForestBonus(structures);
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
            std::pair pair(j, i);
            if (m_Board.at(pair).structure == nullptr &&
                static_cast<int>(m_Board.at(pair).zoneType) & static_cast<int>(qct::ZoneType::NotNone) &&
                checkForRoad(pair))
            {
                double randomValue= QRandomGenerator::global()->bounded(0, 100);
                if (randomValue < 10) {
                    auto buildings = getCompatibleBuildings(m_Board.at(pair).zoneType);
                    int randomIndex = QRandomGenerator::global()->bounded(buildings.size());
                    m_Board.placeBuilding(buildings[randomIndex], {j, i}, m_date);
                    emit meta()->boardChanged();
                }
            }
        }
    }
}

void GameModel::calculateHappyness() {
    int globalHappyness = calculateGlobalHappyness();

    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            std::pair pair(j, i);
            auto house = dynamic_cast<ResidentialBuilding*>(m_Board.at(pair).structure);
            if (house == nullptr)
                continue;

            int enviromentalHappyness =
                calculateEnviromentalHappyness(pair, 5);

            house->setHappyness(globalHappyness + enviromentalHappyness);
        }
    }
}

int GameModel::calculateGlobalHappyness() {
    int happyness = 0;
    happyness += 10 - m_Tax;
    happyness += std::min(0, m_money / 100);

    int serviceZoneCount = 0;
    int industrialZoneCount = 0;
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            switch (m_Board.at({j, i}).zoneType) {
            case qct::ZoneType::Service: {
                ++serviceZoneCount;
            } break;
            case qct::ZoneType::Industrial: {
                ++industrialZoneCount;
            } break;
            default: { } break;
            }
        }
    }
    happyness += -std::abs(serviceZoneCount - industrialZoneCount);

    return happyness;
}

int GameModel::calculateEnviromentalHappyness(std::pair<int, int> position, int radius) {
    // TODO
    return 0;
}

void GameModel::settleInPeople() {

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
        default:
            break;
        }
    }
    m_money -= (stadiumCount * m_costOfMaintainingStadium + policeCount * m_costOfMaintainingPolice);
}

void GameModel::maintainRoads(const std::vector<StructureBase *> &structures)
{
    int roadCount =
        std::accumulate(structures.begin(), structures.end(), 0,
                        [](int accumulated, StructureBase* structure) {
                            return accumulated + (structure->getType() == qct::BuildingType::Road);
                        });

    m_money -= (roadCount * m_costOfMaintainingRoad);
}

void GameModel::maintainForests(const std::vector<StructureBase *> &structures)
{
    int forestCount;
    for (auto structure :structures) {
        if (auto forest = dynamic_cast<Forest*>(structure); forest != nullptr) {
            int years = forest->getBuiltYear().daysTo(m_date) / 365;
            if(years < 11)
                ++forestCount;
        }
    }
    m_money -= forestCount * m_costOfMaintainingForest;
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
        auto above = m_Board.at({row - 1, col}).structure;
        hasNeighbouringRoad |= above != nullptr && above->getType() == qct::BuildingType::Road;
    }
    if (row < getHeight() - 1) {
        auto below = m_Board.at({row + 1, col}).structure;
        hasNeighbouringRoad |= below != nullptr && below->getType() == qct::BuildingType::Road;
    }
    if (col > 0) {
        auto left = m_Board.at({row, col - 1}).structure;
        hasNeighbouringRoad |= left != nullptr && left->getType() == qct::BuildingType::Road;
    }
    if (col < getWidth() - 1) {
        auto right = m_Board.at({row, col + 1}).structure;
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

void GameModel::calculateTax(const std::vector<BuildingBase *> &buildings)
{
    int taxedInhabitants = 0;
    for (auto building :buildings) {
        if (auto house = dynamic_cast<ResidentialBuilding*>(building); house != nullptr) {
            taxedInhabitants += house->getAdultInhabitantCount();
        }
    }
    m_money += (taxedInhabitants * m_Tax);
}

void GameModel::calculatePension(const std::vector<BuildingBase *> &buildings)
{
    int pensionerInhabitants = 0;
    for (auto building :buildings) {
        if (auto house = dynamic_cast<ResidentialBuilding*>(building); house != nullptr) {
            pensionerInhabitants += house->getRetiredInhabitantCount();
        }
    }
    m_money -= (pensionerInhabitants * m_Pension);
}

void GameModel::calculateForestBonus(const std::vector<StructureBase *> &structures)
{
    int forestBonus = 0;
    for (auto structure :structures) {
        if (auto forest = dynamic_cast<Forest*>(structure); forest != nullptr) {
            int years;
            years = forest->getBuiltYear().daysTo(m_date) / 365;
            if(years < 11)
                forestBonus += years * forestBonus;
        }
    }
    m_money += forestBonus;
}

void GameModel::catastrophe()
{
    m_Board.catastrophe();
    emit meta()->releasedCatastrophe();
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
    default:
        return {};
    }
}
