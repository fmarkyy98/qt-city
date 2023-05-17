#pragma once

#include <QWidget>
#include <QTimer>
#include <QStackedWidget>
#include "IGameModel.h"
#include "Enums.h"

namespace Ui {
class GamePage;
}

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(std::shared_ptr<IGameModel> model, QWidget *parent = nullptr);
    ~GamePage();

public slots:
    void onMoneyChanaged(int money);
    void onTimeElapsed();
    //void onBoardChanged();
    void onZonesChanged();
    void onDateChanged(const QDate& date);
    void onLogChanged(const QString& log);

public:
    void newGame();

signals:
    void showMenuPage();

private slots:
    void onSaveButtonClicked();

    void onSlowerButtonClicked();

    void onPauseButtonClicked();

    void onFasterButtonClicked();

    void onExitButtonClicked();

    void onMenuButtonClicked();

    void onRefreshboard();

    void onTableWidget2Clicked(int row, int column);

    void onTableWidget3Clicked(int row, int column);

private:
    void initConnections();
    void changeState();
    void pause();
    void unpause();

    void save();
    void load();
    void placeBuilding(qct::BuildingType buildingType);
    void placeZone(qct::ZoneType zoneType);
    void saveClickedRow(int row, int column);
    QPixmap getPixMap(const StructureBase* type, std::optional<std::pair<int,int>> coordinates=std::nullopt);

private:
    Ui::GamePage *ui;
    std::shared_ptr<IGameModel> m_pGameModel;
    bool isGamePaused;
    int speedLevel;
    bool placingBuilding;
    bool changedBuilding, changedZone;
    int rowInd, columnInd;
    int capacity, peopleCount;
    int peopleHappiness;
    QStringList logList;
    QString info;
    QString priceInfo;
    qct::BuildingType chosenBuildingType;
    qct::ZoneType chosenZoneType;
    std::vector<QString> images;
    QTimer timer;
    QPixmap pixMap;
    QStackedWidget *stackedWidget;

};

