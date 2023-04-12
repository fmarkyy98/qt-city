#include "GameModel.h"

GameModel::GameModel(std::shared_ptr<IFileIOService> fileIOService,
                     QObject *parent)
    : QObject(parent)
    , m_FileIOService(fileIOService)
{}

void GameModel::save(const QString &path) const
{
    std::runtime_error("TODO/marko");
}

void GameModel::load(const QString &path)
{
    std::runtime_error("TODO/marko");
}

int GameModel::getHeight() const
{
    return 15;
}

int GameModel::getWidth() const
{
    return 20;
}

void GameModel::placeZone(ZoneType zoneType, int row, int col)
{
    m_Board.placeZone(zoneType, {row,col});
    emit meta()->onZonesChanged();
}

void GameModel::placeBuilding(BuildingType buildingType, int row, int col)
{
    m_Board.placeBuilding(buildingType, {row,col});
    emit meta()->onBoardChanged();
}

ZoneType GameModel::zoneAt(int row, int col) const
{
    return m_Board.at({row, col}).zoneType;
}

BuildingType GameModel::buildingAt(int row, int col) const
{
    return m_Board.at({row, col}).building->getType();
}

void GameModel::newGame()
{
    m_Board.reset();
}
