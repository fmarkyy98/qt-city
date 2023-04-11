#pragma once

#include "Tile.h"
#include <memory>

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard();
    Tile at(std::pair<int,int>)const;
    void placeBuilding(BuildingType buildingType, std::pair<int, int> position);
    void placeZone(ZoneType zoneType, std::pair<int, int> position);

private:
    std::array<std::array<Tile, 15>, 20> m_Board;
    QList<std::unique_ptr<BuildingBase>> m_Buildings; //new helyett std::make_unique<ResidetalBuidling>()
};
