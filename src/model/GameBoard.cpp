#include "GameBoard.h"
#include "building/ResidentialBuilding.h"
#include "building/Factory.h"
#include "building/Forest.h"
#include "building/Police.h"
#include "building/Road.h"
#include "building/Stadium.h"
#include "building/Store.h"

GameBoard::GameBoard(QDate date, QObject* parent)
    : QObject(parent)
{
    randomForestPlacement(date);
}

std::list<int> GameBoard::serialize() const {

}

void GameBoard::deserialize(std::list<int>& dataList) {

}

const Tile& GameBoard::at(std::pair<int, int> position) const
{
    auto [row, col] = position;
    return m_TileMatrix[row][col];
}

Tile &GameBoard::at(std::pair<int, int> position)
{
    auto [row, col] = position;
    return m_TileMatrix[row][col];
}

void GameBoard::placeBuilding(qct::BuildingType buildingType, std::pair<int, int> position, QDate date)
{
    StructureBase* newStructure;
    auto [row, col] = position;
    switch (buildingType) {
    case qct::BuildingType::Residential: {
        newStructure = new ResidentialBuilding();
    } break;
    case qct::BuildingType::Factory: {
        newStructure = new Factory();
    } break;
    case qct::BuildingType::Police: {
        newStructure = new Police();
    } break;
    case qct::BuildingType::Forest: {
        newStructure = new Forest(date);
    } break;
    case qct::BuildingType::Road: {
        newStructure = new Road();
    } break;
    case qct::BuildingType::Stadium: {
        newStructure = new Stadium();
    } break;
    case qct::BuildingType::Store: {
        newStructure = new Store();
    } break;
    default: {
        throw std::invalid_argument("Invalid BuildingType");
    } break;
    }

    for (int y = col; y < col + newStructure->getHeight(); ++y) {
        for (int x = row; x < row + newStructure->getWidth(); ++x) {
            if(!newStructure->canBuildOnZone(m_TileMatrix[x][y].zoneType)) {
                throw std::invalid_argument("Incompatible Zone type with Building type!");
                return;
            }
        }
    }

    for (int y = col; y < col + newStructure->getHeight(); ++y) {
        for (int x = row; x < row + newStructure->getWidth(); ++x) {
            m_TileMatrix[x][y].structure = newStructure;
        }
    }

    switch(newStructure->getType()) {
    case qct::BuildingType::Road:
    case qct::BuildingType::Forest: {
        m_Structures.push_back(std::unique_ptr<StructureBase>(newStructure));
    } break;
    case qct::BuildingType::Residential:
    case qct::BuildingType::Factory:
    case qct::BuildingType::Store:
    case qct::BuildingType::Police:
    case qct::BuildingType::Stadium: {
        auto building = static_cast<BuildingBase*>(newStructure);
        connect(building,
                &BuildingBase::buildingProcessFinished,
                building,
                [this] { emit buildingProcessFinished(); });
        m_Buildings.push_back(std::unique_ptr<BuildingBase>(building));
    } break;
    default: {} break;
    }
}

void GameBoard::demolishBuilding(std::pair<int, int> position)
{
    auto [row, col] = position;

}

void GameBoard::placeZone(qct::ZoneType zoneType, std::pair<int, int> position)
{
    auto [row, col] = position;
    if (m_TileMatrix[row][col].zoneType != qct::ZoneType::None)
        throw std::invalid_argument("Zone can only placed on empty field.");

    if (m_TileMatrix[row][col].structure != nullptr)
        throw std::invalid_argument("Zone can only placed on field with no building.");

    m_TileMatrix[row][col].zoneType = zoneType;
}

void GameBoard::breakDownZone(std::pair<int, int> position)
{
    auto [row, col] = position;
    if (m_TileMatrix[row][col].zoneType == qct::ZoneType::None)
        throw std::invalid_argument("Empty zone can not be broken down.");

    if (m_TileMatrix[row][col].structure != nullptr)
        throw std::invalid_argument("Zone can not be broken down cause a building is on it.");

    m_TileMatrix[row][col].zoneType = qct::ZoneType::None;
}

const std::vector<BuildingBase*> GameBoard::getBuildings() const
{
    std::vector<BuildingBase*> buildings;
    buildings.reserve(m_Buildings.size());
    for (auto&& building : m_Buildings)
        buildings.push_back(building.get());

    return buildings;
}

const std::vector<StructureBase *> GameBoard::getStructures() const
{
    std::vector<StructureBase*> structures;
    structures.reserve(m_Structures.size());
    for (auto&& structure : m_Structures)
        structures.push_back(structure.get());

    return structures;
}

void GameBoard::catastrophe()
{
    int randomX = QRandomGenerator::global()->bounded(0, 25);;
    int randomY = QRandomGenerator::global()->bounded(0, 15);;

    auto ptr = m_TileMatrix[randomX][randomY].structure;

    if (randomX > 0)
        if (auto above = m_TileMatrix[randomX - 1][randomY].structure; ptr == above)
            above = nullptr;

    if (randomX < 24)
        if (auto below = m_TileMatrix[randomX + 1][randomY].structure; ptr == below)
            below = nullptr;

    if (randomY > 0)
        if (auto left = m_TileMatrix[randomX][randomY - 1].structure; ptr == left)
            left = nullptr;

    if (randomY < 14)
        if (auto right = m_TileMatrix[randomX][randomY + 1].structure; ptr == right)
            right = nullptr;

    std::erase_if(m_Buildings,
                  [ptr](auto&& building) {return building.get() == ptr;});
    std::erase_if(m_Structures,
                  [ptr](auto&& structure) {return structure.get() == ptr;});

    m_TileMatrix[randomX][randomY].structure = nullptr;
    m_TileMatrix[randomX][randomY].zoneType = qct::ZoneType::Radioactive;
}

void GameBoard::reset(QDate date)
{
    for (auto& col : m_TileMatrix) {
        for (auto& tile : col) {
            tile.structure = nullptr;
            tile.zoneType = qct::ZoneType::None;
        }
    }
    m_Buildings.clear();
    m_Structures.clear();
    randomForestPlacement(date);
}

void GameBoard::randomForestPlacement(QDate date)
{
    for (int i = 0; i < m_TileMatrix.size(); ++i) {
        for (int j = 0; j < m_TileMatrix[i].size(); ++j) {
            double randomValue= QRandomGenerator::global()->bounded(0, 100);
            if (randomValue < 2) {
                placeBuilding(qct::BuildingType::Forest, {j, i}, date);
            }
        }
    }
}


