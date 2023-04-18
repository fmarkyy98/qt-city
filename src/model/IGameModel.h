#pragma once

#include "IService.h" 
#include "Enums.h"

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
    virtual QtCity::BuildingType buildingAt(int row, int col) const = 0;
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual QtCity::ZoneType zoneAt(int row, int col) const = 0;
    virtual QtCity::BuildingType buildingAt(int row, int col) const = 0;
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual void placeZone(QtCity::ZoneType zoneType, int row, int col) = 0;
    virtual void placeBuilding(QtCity::BuildingType buildingType, int row, int col) = 0;
    virtual void save(const QString& path) const = 0;
    virtual void load(const QString& path) = 0;
    virtual void newGame() = 0;
    virtual void advanceSimulation() = 0;
};
