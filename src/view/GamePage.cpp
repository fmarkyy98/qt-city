#include "GamePage.h"
#include "ui_GamePage.h"
#include <QDir>
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
    connect(m_pGameModel->meta(), &IGameModel::Meta::onBoardChanged, this, &GamePage::onRefreshboard);
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

void GamePage::onMoneyChanaged()
{
    //TODO
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


    for(int i=0; i<7; i++)
    {
        ui->tableWidget_2->item(0,i)->setData(Qt::DecorationRole, QPixmap(this->images[i]));
        //ui->tableWidget_2->item(1,i)->setData(Qt::TextAlignmentRole,Qt::AlignCenter);
    }
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(ui->tableWidget,&QAbstractItemView::clicked,this,[this](const QModelIndex& idx)->void{
        rowInd=idx.row();
        columnInd=idx.column();
        qDebug() << "Clicked: " << idx.row()<<","<<idx.column();
        qDebug() << "Saved: " << rowInd<<","<<columnInd;
    });

}

void GamePage::onTableWidget2Clicked(int row, int column)
{
    qDebug() << "Column:: " << column;
    switch(column)
    {
        case 0:
            m_pGameModel->placeZone(qct::ZoneType::None, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Road, rowInd, columnInd);
        break;
        case 1:
            m_pGameModel->placeZone(qct::ZoneType::Residential, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Residential, rowInd, columnInd);
        break;
        case 2:
            m_pGameModel->placeZone(qct::ZoneType::Industrial, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Factory, rowInd, columnInd);
        break;
        case 3:
            m_pGameModel->placeZone(qct::ZoneType::Service, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Store, rowInd, columnInd);
        break;
        case 4:
            m_pGameModel->placeZone(qct::ZoneType::Service, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Police, rowInd, columnInd);
        break;
        case 5:
            m_pGameModel->placeZone(qct::ZoneType::Service, rowInd, columnInd);
            m_pGameModel->placeBuilding(qct::BuildingType::Stadium, rowInd, columnInd);
        break;
        case 6:
            m_pGameModel->placeZone(qct::ZoneType::None, row, column);
            m_pGameModel->placeBuilding(qct::BuildingType::Forest, row, column);
        break;
    }
}

void GamePage::onRefreshboard() {
    // Viki TODO minden épülettípusra a megfelelő atribútumokat megjeleníteni.
    for (int y = 0; y < m_pGameModel->getHeight(); y++) {
        for (int x = 0; x < m_pGameModel->getWidth(); x++) {
            auto structure = m_pGameModel->structureAt(x, y);

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

