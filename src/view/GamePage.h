#pragma once

#include <QWidget>
#include <QTimer>
#include "../model/IGameModel.h"
#include "../common/building/BuildingType.h"
#include "../common/zone/ZoneType.h"

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
    void onMoneyChanaged();
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


    void on_tableWidget_2_cellClicked(int row, int column);

private:
    void initConnections();
    void changeState();
    void pause();
    void unpause();

    void save();
    void load();
    void placeBuilding(BuildingType buildingType);
    void placeZone(ZoneType zoneType);
    void saveClickedRow(int row, int column);

private:
    Ui::GamePage *ui;
    std::shared_ptr<IGameModel> m_pGameModel;
    bool isGamePaused;
    int rowInd, columnInd;
    QTimer timer;

};

