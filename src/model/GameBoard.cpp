#include "GameBoard.h"
#include "building/ResidentialBuilding.h"
#include "building/Factory.h"

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

void GameBoard::placeBuilding(BuildingType buildingType, std::pair<int, int> position)
{
    std::unique_ptr<BuildingBase> newBuilding;
    auto [row, col] = position;
    switch (buildingType) {
    case BuildingType::Residential:
        newBuilding = std::make_unique<ResidentialBuilding>();
        break;
    case BuildingType::Factory:
        newBuilding = std::make_unique<Factory>();
        break;
    case BuildingType::Police:
        newBuilding = std::make_unique<ResidentialBuilding>(); //POLICE
        break;
    }
    //TODO epulet teljes alapteruletere meg kell nezni hogy kompatibilis zona van e ott,
    //ha ez mindegyikre teljesul, akkor az osszes tile-ra fel kell helyezni a raw pointert(newBuilding.get())
    // ha nem teljesul akkor early return
    if(!newBuilding->canBuildOnZone(m_TileMatrix[row][col].zoneType))
        return;

    m_TileMatrix[row][col].building = newBuilding.get();
    m_Buildings.push_back(std::move(newBuilding));
}

void GameBoard::placeZone(ZoneType zoneType, std::pair<int, int> position)
{
    auto [row, col] = position;
    m_TileMatrix[row][col].zoneType = zoneType;
    // TODO --dinero
}

void GameBoard::reset()
{
    for (auto& col : m_TileMatrix) {
        for (auto& tile : col) {
            tile.building = nullptr;
            tile.zoneType = ZoneType::None;
        }
    }
}


