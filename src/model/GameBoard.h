#pragma once

#include "Tile.h"
#include <memory>
#include <QDate>

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QDate date, QObject* parent = nullptr);
    std::list<int> serialize() const;
    void deserialize(std::list<int>& dataList);
    const Tile& at(std::pair<int,int> position)const;
    Tile& at(std::pair<int,int> position);
    void placeBuilding(qct::BuildingType buildingType, std::pair<int, int> position, QDate date);
    void placeZone(qct::ZoneType zoneType, std::pair<int, int> position);
    void breakDownZone(std::pair<int, int> position);
    const std::vector<BuildingBase*> getBuildings() const;
    const std::vector<StructureBase*> getStructures() const;
    void catastrophe();//TODO
    void reset(QDate date);
    void randomForestPlacement(QDate date);

private:
    std::array<std::array<Tile, 25>, 15> m_TileMatrix;
    std::vector<std::unique_ptr<BuildingBase>> m_Buildings;
    std::vector<std::unique_ptr<StructureBase>> m_Structures;
};
