#pragma once

#include <QObject>

#include <memory>
#include <QDate>
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
    int getCostOfPlacingZone() const override;
    int getCostOfBuildingBuilding() const override;
    int getGlobalInhabitantCount() const override;
    int getGlobalInhabitantCapacity() const override;
    int getGlobalWorkerCount() const override;
    int getGlobalWorkerCapacity() const override;
    int getGlobalHappyness() const override;
    void placeZone(qct::ZoneType zoneType, int row, int col) override;
    void breakDownZone(int row, int col) override;
    void placeBuilding(qct::BuildingType buildingType, int row, int col) override;
    void evolveBuilding(int row, int col) override;
    void demolishBuilding(int row, int col) override;
    qct::ZoneType zoneAt(int row, int col) const override;
    const StructureBase* structureAt(int row, int col) const override;
    void newGame() override;
    void advanceSimulation() override;

private:
    void yearPassed(const std::vector<BuildingBase*>& buildings,
                    const std::vector<StructureBase*>& structures);
    void advanceBuildingProcesses(const std::vector<BuildingBase*>& buildings);
    void distributeInhabitantsToWorkplaces(const std::vector<BuildingBase*>& buildings);
    void increaseMoney(const std::vector<BuildingBase*>& buildings);
    void buildOnRandomZone();
    void calculateHappyness();
    int calculateGlobalHappyness();
    int calculateEnviromentalHappyness(std::pair<int, int> position, int radius);
    void settleInPeople(const std::vector<BuildingBase*>& buildings);
    void maintainCity(const std::vector<BuildingBase*>& buildings);
    void maintainRoads(const std::vector<StructureBase*>& structures);
    void maintainForests(const std::vector<StructureBase*>& structures);
    void increaseInhabitantAge(const std::vector<BuildingBase*>& buildings);
    bool checkForRoad(std::pair<int, int> position);
    bool checkForForest(std::pair<int, int> position);
    void calculateTax(const std::vector<BuildingBase*>& buildings);
    void calculatePension(const std::vector<BuildingBase*>& buildings);
    void calculateForestBonus(const std::vector<StructureBase*>& structures);
    void catastrophe();

private:
    static QList<qct::BuildingType> getCompatibleBuildings(qct::ZoneType);

private:
    GameBoard m_Board;
    std::shared_ptr<IFileIOService> m_FileIOService;
    int m_money;
    QDate m_date = m_dateAtStart;

private:
    static const QDate m_dateAtStart;
    static constexpr int m_moneyAtStart = 500000;
    static constexpr int m_costOfPlacingZone = 500;
    static constexpr int m_costOfBuildingBuilding = 750;
    static constexpr int m_costOfMaintainingPolice = 1000;
    static constexpr int m_costOfMaintainingStadium = 2000;
    static constexpr int m_costOfMaintainingRoad = 50;
    static constexpr int m_costOfMaintainingForest = 25;
    static constexpr int m_ForestBonus = 50;
    static constexpr int m_Tax = 2;
    static constexpr int m_Pension = 1;
};
