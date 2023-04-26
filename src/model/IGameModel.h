#pragma once

#include "export/IService.h"
#include "export/Enums.h"

class StructureBase;

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
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual qct::ZoneType zoneAt(int row, int col) const = 0;
    virtual const StructureBase* structureAt(int row, int col) const = 0;
    virtual void placeZone(qct::ZoneType zoneType, int row, int col) = 0;
    virtual void placeBuilding(qct::BuildingType buildingType, int row, int col) = 0;
    virtual void save(const QString& path) const = 0;
    virtual void load(const QString& path) = 0;
    virtual void newGame() = 0;
    virtual void advanceSimulation() = 0;
};
