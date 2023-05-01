#pragma once

#include <QObject>

#include <memory>
#include "IGameModel.h"
#include "GameBoard.h"
#include "../persistence/export/IFileIOService.h"

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
    void breakDownZone(int row, int col);
    void placeBuilding(qct::BuildingType buildingType, int row, int col) override;
    qct::ZoneType zoneAt(int row, int col) const override;
    const StructureBase* structureAt(int row, int col) const override;
    void newGame() override;
    void advanceSimulation() override;
    void yearPassed(const std::vector<BuildingBase *> &buildings);

private:
    bool canPlaceBuilding(); //TODO
    void advanceBuildingProcesses(const std::vector<BuildingBase *> &buildings);
    void increaseInhabitantAge(const std::vector<BuildingBase *> &buildings);
    void distributeInhabitantsToWorkplaces(const std::vector<BuildingBase *> &buildings);
    void increaseMoney(const std::vector<BuildingBase *> &buildings);

private:
    GameBoard m_Board;
    std::shared_ptr<IFileIOService> m_FileIOService;
    int m_money;
    int m_moneyAtStart = 500000;
    static constexpr int m_costOfPlacingZone = 500;
    static constexpr int m_costOfBreakingZone = 100;
    static constexpr int m_costOfBuildingBuilding = 750;
    static constexpr int m_costOfMaintainingPolice = 1000;
    static constexpr int m_costOfMaintainingStadium =2000 ;
};
