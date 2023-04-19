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
    std::unique_ptr<StructureBase> newBuilding;
    auto [row, col] = position;
    switch (buildingType) {
    case qct::BuildingType::Residential:
        newBuilding = std::make_unique<ResidentialBuilding>();
        break;
    case qct::BuildingType::Factory:
        newBuilding = std::make_unique<Factory>();
        break;
    case qct::BuildingType::Police:
        newBuilding = std::make_unique<Police>();
        break;
    case qct::BuildingType::Forest:
        newBuilding = std::make_unique<Forest>();
        break;
    case qct::BuildingType::Road:
        newBuilding = std::make_unique<Road>();
        break;
    case qct::BuildingType::Stadium:
        newBuilding = std::make_unique<Stadium>();
        break;
    case qct::BuildingType::Store:
        newBuilding = std::make_unique<Store>();
        break;
    }
    //TODO epulet teljes alapteruletere meg kell nezni hogy kompatibilis zona van e ott,
    //ha ez mindegyikre teljesul, akkor az osszes tile-ra fel kell helyezni a raw pointert(newBuilding.get())
    // ha nem teljesul akkor early return
    //ciklusokkal
    if(!newBuilding->canBuildOnZone(m_TileMatrix[row][col].zoneType))
        return;

    m_TileMatrix[row][col].structure = newBuilding.get();

    if(std::dynamic_pointer_cast<BuildingBase>(newBuilding) != nullptr)
        m_Buildings.push_back(std::move(newBuilding));
    else
        m_Structures.push_back(std::move(newBuilding));
}

void GameBoard::placeZone(qct::ZoneType zoneType, std::pair<int, int> position)
{
    auto [row, col] = position;
    if(m_TileMatrix[row][col].zoneType == qct::ZoneType::None){
        m_TileMatrix[row][col].zoneType = zoneType;
    }
    else
    {
        std::runtime_error("TODO");
    }
}

void GameBoard::breakDownZone(std::pair<int, int> position)
{
    auto [row, col] = position;
    if(m_TileMatrix[row][col].structure == nullptr){
        m_TileMatrix[row][col].zoneType = qct::ZoneType::None;
    }
    else
    {
        std::runtime_error("TODO");
    }
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


