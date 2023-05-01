#pragma once

#include <QWidget>
#include <QTimer>
#include <QStackedWidget>
#include "../model/IGameModel.h"
#include "../model/export/Enums.h"

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
    void onBoardChanged();
    void onZonesChanged();

public:
    void newGame();

signals:
    void showMenuPage();

private slots:
    void onSaveButtonClicked();

    void onSettingsButtonClicked();

    void onSlowerButtonClicked();

    void onPauseButtonClicked();

    void onFasterButtonClicked();

    void onExitButtonClicked();

    void onMenuButtonClicked();

    void onRefreshboard();

    void onTableWidget2Clicked(int row, int column);

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
    QPixmap getPixMap(qct::BuildingType type);

private:
    Ui::GamePage *ui;
    std::shared_ptr<IGameModel> m_pGameModel;
    bool isGamePaused;
    bool placingBuilding;
    bool changedBuilding, changedZone;
    int rowInd, columnInd;
    qct::BuildingType chosenBuildingType;
    qct::ZoneType chosenZoneType;
    std::vector<QString> images;
    QTimer timer;
    QPixmap pixMap;
    QStackedWidget *stackedWidget;

};

