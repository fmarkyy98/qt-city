#pragma once

#include <QObject>

#include "IGameModel.h"
#include "../persistence/IFileIOService.h"

class GameModel
    : public QObject
    , public IGameModel
{
    Q_OBJECT

public:
    GameModel(std::shared_ptr<IFileIOService> fileIOService) {}
    virtual ZoneType zoneAt(int row, int col) const {return ZoneType::None;}
    virtual void placeZone(ZoneType zoneType, int row, int col) {};
    virtual void save(const QString& path) const {};
    virtual void load(const QString& path) {};
    virtual int getHeight() {return 15;}
    virtual int getWidth() {return 20;}
};
