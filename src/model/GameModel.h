#pragma once

#include <QObject>

#include <memory>
#include "IGameModel.h"
#include "GameBoard.h"
#include "persistence/export/IFileIOService.h"

class GameModel
    : public QObject
    , public IGameModel
{
    Q_OBJECT

public:
    explicit GameModel(std::shared_ptr<IFileIOService> fileIOService,
                       QObject* parent = nullptr);
    void save(const QString& path) const override;
    void load(const QString& path) override;
    int getHeight() const override;
    int getWidth() const override;
    void placeZone(qct::ZoneType zoneType, int row, int col) override;
    void placeBuilding(qct::BuildingType buildingType, int row, int col) override;
    qct::ZoneType zoneAt(int row, int col) const override;
    qct::BuildingType buildingAt(int row, int col) const override;
    void newGame() override;
    void advanceSimulation() override;

private:
    GameBoard m_Board;
    std::shared_ptr<IFileIOService> m_FileIOService;

private:
    bool canPlaceBuilding(); //TODO
};
