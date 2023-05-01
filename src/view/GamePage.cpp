#include "GamePage.h"
#include "ui_GamePage.h"
#include <QDir>
#include <QMessageBox>
#include <QtGui>
#include <iostream>

#include "../model/building/ResidentialBuilding.h"
#include "../model/building/Factory.h"
#include "../model/building/Forest.h"
#include "../model/building/Police.h"
#include "../model/building/Road.h"
#include "../model/building/Stadium.h"
#include "../model/building/Store.h"

GamePage::GamePage(std::shared_ptr<IGameModel> model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePage)
    , m_pGameModel(model)
{
    ui->setupUi(this);
    initConnections();
    rowInd = 0;
    columnInd = 0;
    images = {":/images/road",
              ":/images/house",
              ":/images/factory",
              ":/images/store",
              ":/images/police",
              ":/images/stadium",
              ":/images/forest"};
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(ui->tableWidget_2);
    stackedWidget->addWidget(ui->tableWidget_3);
    stackedWidget->setCurrentWidget(ui->tableWidget_2);
    ui->verticalLayout->insertWidget(2,stackedWidget);
}

GamePage::~GamePage()
{
    delete ui;
}

void GamePage::onSaveButtonClicked()
{
    //TODO
}


void GamePage::onSettingsButtonClicked()
{
    //TODO
}


void GamePage::onSlowerButtonClicked()
{
    //TODO
}


void GamePage::onPauseButtonClicked()
{
    //TODO
}


void GamePage::onFasterButtonClicked()
{
    //TODO
}


void GamePage::onExitButtonClicked()
{
    //TODO
}

void GamePage::onMenuButtonClicked()
{
    emit showMenuPage();
}

void GamePage::initConnections()
{
    connect(ui->saveButton, &QPushButton::clicked, this, &GamePage::onSaveButtonClicked);
    connect(ui->menuButton, &QPushButton::clicked, this, &GamePage::onMenuButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &GamePage::onExitButtonClicked);
    connect(ui->fasterButton, &QPushButton::clicked, this, &GamePage::onFasterButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &GamePage::onPauseButtonClicked);
    connect(ui->slowerButton, &QPushButton::clicked, this, &GamePage::onSlowerButtonClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &GamePage::onSettingsButtonClicked);
    connect(ui->tableWidget_2, &QTableWidget::cellClicked, this, &GamePage::onTableWidget2Clicked);
    connect(m_pGameModel->meta(), &IGameModel::Meta::boardChanged, this, &GamePage::onRefreshboard);
    connect(m_pGameModel->meta(), &IGameModel::Meta::moneyChanged, this, &GamePage::onMoneyChanaged);
}

void GamePage::onTimeElapsed()
{
    //TODO
}

void GamePage::onBoardChanged()
{
    //TODO
}

void GamePage::onZonesChanged()
{
    //TODO
}

void GamePage::onMoneyChanaged(int money)
{
    ui->label_3->setText("Pemz: " + QString::number(money) + " csengőPengő");
}

void GamePage::newGame()
{
    //m_pGameModel->newGame();
    //Ui::GamePage->setStyleSheet("background-image: url(:/images/background)");

    std::cerr<<m_pGameModel->getHeight();
    std::cerr<<m_pGameModel->getWidth();
    ui->tableWidget->setRowCount(m_pGameModel->getWidth());
    ui->tableWidget->setColumnCount(m_pGameModel->getHeight());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int y=0;y<m_pGameModel->getHeight();y++)
    {
        for(int x=0;x<m_pGameModel->getWidth();x++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem;
            newItem->setBackground(QColor(113, 168, 93));
            ui->tableWidget->setItem(x, y, newItem);

        }
    }


    for(int i=1; i<7; i++)
    {
        ui->tableWidget_2->item(0,i)->setData(Qt::DecorationRole, QPixmap(this->images[i-1]));
    }
    ui->tableWidget_2->item(0,8)->setText("Choose a building or Zone!");
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    connect(ui->tableWidget,&QAbstractItemView::clicked,this,[this](const QModelIndex& idx)->void{
        rowInd=idx.row();
        columnInd=idx.column();
        if(m_pGameModel->structureAt(rowInd, columnInd)==nullptr) stackedWidget->setCurrentWidget(ui->tableWidget_2);
        else stackedWidget->setCurrentWidget(ui->tableWidget_3);
        qDebug() << "Clicked: " << idx.row()<<","<<idx.column();
        qDebug() << "Saved: " << rowInd<<","<<columnInd;
    });

}

void GamePage::onTableWidget2Clicked(int row, int column)
{
    //TODO: epuletet nonetypera le lehet rakni akkor is ha pl road van mar ott
    QMessageBox messageBox;
    qDebug() << "Column:: " << column;
    switch(column)
    {
        case 0:
            //ui->tableWidget_2->item(0,8)->setText("Price: \nCapacity: ");
        break;
        case 1:
            if (row == 0) {
                chosenBuildingType=qct::BuildingType::Road;
                placingBuilding=true;
            }
        break;
        case 2:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Residential;
            } else {
                chosenZoneType=qct::ZoneType::Residential;
                placingBuilding=false;
            }
        break;
        case 3:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Factory;
            } else {
                chosenZoneType=qct::ZoneType::Industrial;
                placingBuilding=false;
            }
        break;
        case 4:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Store;
            } else {
                chosenZoneType=qct::ZoneType::Service;
                placingBuilding=false;
            }
        break;
        case 5:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Police;
            } else {
                chosenZoneType=qct::ZoneType::Service;
                placingBuilding=false;
            }
        break;
        case 6:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Stadium;
            } else {
                chosenZoneType=qct::ZoneType::Service;
                placingBuilding=false;
            }

        break;
        case 7:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Forest;
            }
        break;
        case 8:
            if (row == 0) {
                //TODO
            } else {
                try {
                    if (placingBuilding) {
                        m_pGameModel->placeBuilding(chosenBuildingType, rowInd, columnInd);
                    } else if (!placingBuilding) {
                        m_pGameModel->placeZone(chosenZoneType, rowInd, columnInd);
                    }
                    changedBuilding = false;
                    changedZone = false;
                    chosenBuildingType=qct::BuildingType::None;
                    chosenZoneType=qct::ZoneType::None;
                } catch (const std::invalid_argument& e) {
                    messageBox.critical(0,"Error",e.what());
                }
            }
        break;
        }
}

void GamePage::onRefreshboard() {
    // Viki TODO minden épülettípusra a megfelelő atribútumokat megjeleníteni.
    for (int y = 0; y < m_pGameModel->getHeight(); y++) {
        for (int x = 0; x < m_pGameModel->getWidth(); x++) {
            auto structure = m_pGameModel->structureAt(x, y);
            if (structure == nullptr)
                continue;

            switch (structure->getType()) {
            case qct::BuildingType::Road: {
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/road"));
            } break;

            case qct::BuildingType::Store: {
                auto store = static_cast<const Store*>(structure);
                int leve = store->getLevel();
                // TODO level alapján elágazni
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/store"));
            } break;

            case qct::BuildingType::Stadium: {
                auto stadium = static_cast<const Stadium*>(structure);
                // TODO
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/stadium"));
            } break;

            case qct::BuildingType::Forest: {
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/forest"));
            } break;

            case qct::BuildingType::Factory: {
                auto factory = static_cast<const Factory*>(structure);
                // TODO
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/factory"));
            } break;

            case qct::BuildingType::Residential: {
                auto residential = static_cast<const ResidentialBuilding*>(structure);
                // TODO
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/house"));
            } break;

            case qct::BuildingType::Police: {
                auto police = static_cast<const Police*>(structure);
                // TODO
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/police"));
            } break;

            case qct::BuildingType::None: {
                ui->tableWidget->item(x,y)->setData(Qt::DecorationRole, QPixmap(":/images/free"));
            } break;

            default: {} break;
            }
        }
    }
}

