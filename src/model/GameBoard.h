#pragma once

#include "Tile.h"
#include <memory>

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent = nullptr);
    const Tile& at(std::pair<int,int> position)const;
    Tile& at(std::pair<int,int> position);
<<<<<<< HEAD
    void placeBuilding(BuildingType buildingType, std::pair<int, int> position);
    void placeZone(ZoneType zoneType, std::pair<int, int> position);
    void breakDownZone(std::pair<int, int> position);
    void catastrophe();//TODO
=======
    void placeBuilding(qct::BuildingType buildingType, std::pair<int, int> position);
    void placeZone(qct::ZoneType zoneType, std::pair<int, int> position);
>>>>>>> master
    void reset();

private:
    std::array<std::array<Tile, 20>, 15> m_TileMatrix;
    std::vector<std::unique_ptr<BuildingBase>> m_Buildings;
};
