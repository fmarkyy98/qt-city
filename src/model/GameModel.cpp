#include "GameModel.h"
#include "QtCore/qdebug.h"

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
    return 20;
}

int GameModel::getWidth() const
{
    return 15;
}

void GameModel::placeZone(ZoneType zoneType, int row, int col)
{
    //Placing a zone costs 500
    if(m_money >= 500){
        m_Board.placeZone(zoneType, {row,col});
        emit meta()->onZonesChanged();
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

void GameModel::breakDownZone(int row, int col)
{
    //Breaking down a zone costs 500
    if(m_money >= 100){
        m_Board.breakDownZone({row,col});
        emit meta()->onZonesChanged();
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

void GameModel::placeBuilding(BuildingType buildingType, int row, int col)
{
    //Building a building costs 500
    if(m_money >= 750){
    m_Board.placeBuilding(buildingType, {row,col});
    emit meta()->onBoardChanged();
    emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

ZoneType GameModel::zoneAt(int row, int col) const
{
    return m_Board.at({row, col}).zoneType;
}

BuildingType GameModel::buildingAt(int row, int col) const
{
    auto building = m_Board.at({row, col}).building;
    if(building != nullptr)
    {
        qDebug() << "buildingAt: " << row<<","<<col;
    }
    return building != nullptr
        ? building->getType()
        : BuildingType::None;
}

void GameModel::newGame()
{
    m_Board.reset();
}

void GameModel::advanceSimulation()
{
    //TODO
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
            if(m_Board)//TODO
        }
    }
    emit meta()->onMoneyChanged(m_money);
}
