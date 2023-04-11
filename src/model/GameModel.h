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
    explicit GameModel(std::shared_ptr<IFileIOService> fileIOService);
    void save(const QString& path) const override;
    void load(const QString& path) override;

private:
    GameBoard m_Board;
    std::shared_ptr<IFileIOService> m_FileIOService;

private:
    bool canPlaceBuilding(); //TODO
};
