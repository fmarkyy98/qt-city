#pragma once

#include <QObject>

#include <memory>
#include "IGameModel.h"
#include "GameBoard.h"
#include "../persistence/IFileIOService.h"

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
    void placeZone(ZoneType zoneType, int row, int col) override;
    void placeBuilding(BuildingType buildingType, int row, int col) override;
    ZoneType zoneAt(int row, int col) const override;
    BuildingType buildingAt(int row, int col) const override;
    void newGame() override;

private:
    GameBoard m_Board;
    std::shared_ptr<IFileIOService> m_FileIOService;

private:
    bool canPlaceBuilding(); //TODO
};
