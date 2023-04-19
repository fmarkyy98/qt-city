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

void GameModel::placeZone(qct::ZoneType zoneType, int row, int col)
{
    if(m_money >= m_costOfPlacingZone){
        m_Board.placeZone(zoneType, {row,col});
        emit meta()->onZonesChanged();
        m_money -= m_costOfPlacingZone;
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

void GameModel::breakDownZone(int row, int col)
{
    if(m_money >= m_costOfBreakingZone){
        m_Board.breakDownZone({row,col});
        emit meta()->onZonesChanged();
        m_money -= m_costOfBreakingZone;
        emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

void GameModel::placeBuilding(qct::BuildingType buildingType, int row, int col)
{
    if(m_money >= m_costOfBuildingBuilding){
    m_Board.placeBuilding(buildingType, {row,col});
    emit meta()->onBoardChanged();
    m_money -= m_costOfBuildingBuilding;
    emit meta()->onMoneyChanged(m_money);
    }
    else
    {
        std::runtime_error("TODO");
    }
}

qct::ZoneType GameModel::zoneAt(int row, int col) const
{
    return m_Board.at({row, col}).zoneType;
}

qct::BuildingType GameModel::buildingAt(int row, int col) const
{
    auto building = m_Board.at({row, col}).structure;
    if(building != nullptr)
    {
        qDebug() << "buildingAt: " << row<<","<<col;
    }
    return building != nullptr
        ? building->getType()
        : qct::BuildingType::None;
}

void GameModel::newGame()
{
    m_Board.reset();
    m_money = m_moneyAtStart;
    emit meta()->onMoneyChanged(m_money);
}

void GameModel::advanceSimulation()
{
    //TODO
    for (int i = 0; i < getHeight(); ++i) {
        for (int j = 0; j < getWidth(); ++j) {
        }
    }
}
