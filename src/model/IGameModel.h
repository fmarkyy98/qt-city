#pragma once

#include "../common/IService.h" // TODO normális útvonalat megadni.
#include "../common/zone/ZoneType.h"
#include "../common/building/BuildingType.h"

class IGameModelMeta : public details::IServiceMeta {
    Q_OBJECT
signals:
    void onMoneyChanged(int money);
    void onBoardChanged();
    void onZonesChanged();
};

class IGameModel : public IService<IGameModelMeta>
{
public:
    virtual ZoneType zoneAt(int row, int col) const = 0;
    virtual BuildingType buildingAt(int row, int col) const = 0;
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual void placeZone(ZoneType zoneType, int row, int col) = 0;
    virtual void placeBuilding(BuildingType buildingType, int row, int col) = 0;
    virtual void save(const QString& path) const = 0;
    virtual void load(const QString& path) = 0;
    virtual void newGame() = 0;
};
