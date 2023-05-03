#pragma once

#include "export/IService.h"
#include "export/Enums.h"
#include <QDate>

class StructureBase;

class IGameModelMeta : public details::IServiceMeta {
    Q_OBJECT
signals:
    void moneyChanged(int money);
    void boardChanged();
    void zonesChanged();
    void dateChanged(const QDate& date);
    void releasedCatastrophe();
};

class IGameModel : public IService<IGameModelMeta>
{
public:
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual int getCostOfPlacingZone() const = 0;
    virtual int getCostOfBuildingBuilding() const = 0;
    virtual int getGlobalInhabitantCount() const = 0;
    virtual int getGlobalInhabitantCapacity() const = 0;
    virtual int getGlobalWorkerCount() const = 0;
    virtual int getGlobalWorkerCapacity() const = 0;
    virtual qct::ZoneType zoneAt(int row, int col) const = 0;
    virtual const StructureBase* structureAt(int row, int col) const = 0;
    virtual void placeZone(qct::ZoneType zoneType, int row, int col) = 0;
    virtual void breakDownZone(int row, int col) = 0;
    virtual void placeBuilding(qct::BuildingType buildingType, int row, int col) = 0;
    virtual void demolishBuilding(int row, int col) = 0;
    virtual void save(const QString& path) const = 0;
    virtual void load(const QString& path) = 0;
    virtual void newGame() = 0;
    virtual void advanceSimulation() = 0;
    virtual void evolveBuilding(const StructureBase* structure);
};
