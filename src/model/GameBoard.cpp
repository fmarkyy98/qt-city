#include "GameBoard.h"
#include "building/ResidentialBuilding.h"
#include "building/Factory.h"
#include "building/Forest.h"
#include "building/Police.h"
#include "building/Road.h"
#include "building/Stadium.h"
#include "building/Store.h"

GameBoard::GameBoard(QObject* parent)
    : QObject(parent)
{}

std::list<int> GameBoard::serialize() const {
    std::list<int> dataList;
    for (int i = 0; i < m_TileMatrix.size(); ++i) {
        for (int j = 0; j < m_TileMatrix[i].size(); ++j) {
            dataList.push_back(static_cast<int>(m_TileMatrix[j][i].zoneType));
        }
    }

    auto serializeStructureContainer = [this, &dataList](const auto& container) {
        dataList.push_back(container.size());
        for (auto&& structure : container) {
            dataList.push_back(static_cast<int>(structure->getType()));
            auto [topLeftX, topLeftY] = indexOfStructure(structure.get());
            auto [heigth, width] = structure->getSize();
            auto bottomRightX = topLeftX + heigth - 1;
            auto bottomRightY = topLeftY + width - 1;
            dataList.push_back(topLeftX);
            dataList.push_back(topLeftY);
            dataList.push_back(bottomRightX);
            dataList.push_back(bottomRightY);

            dataList.merge(structure->serialize());
        }
    };
    serializeStructureContainer(m_Buildings);
    serializeStructureContainer(m_Structures);

    return dataList;
}

void GameBoard::deserialize(std::list<int>& dataList) {
    for (int i = 0; i < m_TileMatrix.size(); ++i) {
        for (int j = 0; j < m_TileMatrix[i].size(); ++j) {
            m_TileMatrix[j][i].zoneType = static_cast<qct::ZoneType>(dataList.front());
            dataList.pop_front();
        }
    }

    for (int _ = 0; _ < 2; ++_) {
        int n = dataList.front(); dataList.pop_front();
        for (int _ = 0; _ < n; ++_) {
            StructureBase* structure = nullptr;

            auto type = static_cast<qct::BuildingType>(dataList.front()); dataList.pop_front();
            switch (type) {
            case qct::BuildingType::Road: {
                structure = new Road();
            } break;
            case qct::BuildingType::Forest: {
                structure = new Forest();
            } break;
            case qct::BuildingType::Residential: {
                structure = new ResidentialBuilding();
            } break;
            case qct::BuildingType::Factory: {
                structure = new Factory();
            } break;
            case qct::BuildingType::Store: {
                structure = new Store();
            } break;
            case qct::BuildingType::Police: {
                structure = new Police();
            } break;
            case qct::BuildingType::Stadium: {
                structure = new Stadium();
            } break;
            default: {
            } break;
            }

            int topLeftX = dataList.front(); dataList.pop_front();
            int topLeftY =  dataList.front(); dataList.pop_front();
            int bottomRightX =  dataList.front(); dataList.pop_front();
            int bottomRightY =  dataList.front(); dataList.pop_front();
            for (int i = topLeftX; i <= bottomRightX; ++i) {
                for (int j = topLeftY; j <= bottomRightY; ++j) {
                    m_TileMatrix[j][i].structure = structure;
                }
            }

            switch(structure->getType()) {
            case qct::BuildingType::Road:
            case qct::BuildingType::Forest: {
                m_Structures.push_back(std::unique_ptr<StructureBase>(structure));
            } break;
            case qct::BuildingType::Residential:
            case qct::BuildingType::Factory:
            case qct::BuildingType::Store:
            case qct::BuildingType::Police:
            case qct::BuildingType::Stadium: {
                m_Buildings.push_back(std::unique_ptr<BuildingBase>(static_cast<BuildingBase*>(structure)));
            } break;
            default: {} break;
            }

            structure->deserialize(dataList);
        }
    }
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


void GameBoard::reset()
{
    for (auto& col : m_TileMatrix) {
        for (auto& tile : col) {
            tile.structure = nullptr;
            tile.zoneType = qct::ZoneType::None;
        }
    }
}

std::pair<int, int> GameBoard::indexOfStructure(StructureBase* structure) const {
    for (int i = 0; i < m_TileMatrix.size(); ++i)
        for (int j = 0; j < m_TileMatrix[i].size(); ++j)
            if (m_TileMatrix[j][i].structure == structure)
                return {j, i};

    throw std::runtime_error("Atleast one tile should point to this object");
}
