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
    StructureBase* newBuilding;
    auto [row, col] = position;
    switch (buildingType) {
    case qct::BuildingType::Residential: {
        newBuilding = new ResidentialBuilding();
    } break;
    case qct::BuildingType::Factory: {
        newBuilding = new Factory();
    } break;
    case qct::BuildingType::Police: {
        newBuilding = new Police();
    } break;
    case qct::BuildingType::Forest: {
        newBuilding = new Forest(date);
    } break;
    case qct::BuildingType::Road: {
        newBuilding = new Road();
    } break;
    case qct::BuildingType::Stadium: {
        newBuilding = new Stadium();
    } break;
    case qct::BuildingType::Store: {
        newBuilding = new Store();
    } break;
    default: {
        throw std::invalid_argument("Invalid BuildingType");
    } break;
    }

    for (int y = col; y < col + newBuilding->getHeight(); ++y) {
        for (int x = row; x < row + newBuilding->getWidth(); ++x) {
            if(!newBuilding->canBuildOnZone(m_TileMatrix[x][y].zoneType)) {
                throw std::invalid_argument("Incompatible Zone type with Building type!");
                return;
            }
        }
    }

    for (int y = col; y < col + newBuilding->getHeight(); ++y) {
        for (int x = row; x < row + newBuilding->getWidth(); ++x) {
            m_TileMatrix[x][y].structure = newBuilding;
        }
    }

    switch(newBuilding->getType()) {
    case qct::BuildingType::Road:
    case qct::BuildingType::Forest: {
        m_Structures.push_back(std::unique_ptr<StructureBase>(newBuilding));
    } break;
    case qct::BuildingType::Residential:
    case qct::BuildingType::Factory:
    case qct::BuildingType::Store:
    case qct::BuildingType::Police:
    case qct::BuildingType::Stadium: {
        m_Buildings.push_back(std::unique_ptr<BuildingBase>(static_cast<BuildingBase*>(newBuilding)));
    } break;
    default: {} break;
    }
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


