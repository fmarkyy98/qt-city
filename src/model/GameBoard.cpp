#include "GameBoard.h"
#include "building/ResidentialBuilding.h"
#include "building/Factory.h"
#include "building/Forest.h"
#include "building/Police.h"
#include "building/Road.h"
#include "building/Stadium.h"
#include "building/Store.h"

GameBoard::GameBoard(QObject* parent) : QObject(parent){}

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

void GameBoard::placeBuilding(qct::BuildingType buildingType, std::pair<int, int> position)
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
        newBuilding = new Forest();
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
    //TODO epulet teljes alapteruletere meg kell nezni hogy kompatibilis zona van e ott,
    //ha ez mindegyikre teljesul, akkor az osszes tile-ra fel kell helyezni a raw pointert(newBuilding.get())
    // ha nem teljesul akkor early return
    //ciklusokkal
    if(!newBuilding->canBuildOnZone(m_TileMatrix[row][col].zoneType))
        throw std::invalid_argument("Incompatible Zone type with Building type!");

    m_TileMatrix[row][col].structure = newBuilding;

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


void GameBoard::reset()
{
    for (auto& col : m_TileMatrix) {
        for (auto& tile : col) {
            tile.structure = nullptr;
            tile.zoneType = qct::ZoneType::None;
        }
    }
}

