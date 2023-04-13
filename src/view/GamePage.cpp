#include "GamePage.h"
#include "ui_GamePage.h"
#include <QDir>
#include <iostream>

GamePage::GamePage(std::shared_ptr<IGameModel> model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePage)
    , m_pGameModel(model)
{
    ui->setupUi(this);
    initConnections();
    rowInd = 0;
    columnInd = 0;
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
    std::cerr<<m_pGameModel->getHeight();
    std::cerr<<m_pGameModel->getWidth();
    ui->tableWidget->setRowCount(m_pGameModel->getWidth());
    ui->tableWidget->setColumnCount(m_pGameModel->getHeight());
    for(int y=0;y<m_pGameModel->getHeight();y++)
    {
        for(int x=0;x<m_pGameModel->getWidth();x++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem;
            //newItem->setIcon(QIcon("/Users/nemesviko/Desktop/QtCity/qt-city/resource/forest-icon-png-7089.png"));
            newItem->setIcon(QIcon(":/images/free"));

            ui->tableWidget->setItem(x, y, newItem);

        }
    }

    connect(ui->tableWidget,&QAbstractItemView::clicked,this,[this](const QModelIndex& idx)->void{
        rowInd=idx.row();
        columnInd=idx.column();
        qDebug() << "Clicked: " << idx.row()<<","<<idx.column();
        qDebug() << "Saved: " << rowInd<<","<<columnInd;
    });

}

void GamePage::onTableWidget2Clicked(int row, int column)
{
    //if(column==0) m_pGameModel->placeZone()  -road nincsen?
    switch(column)
    {
        case 0:
            m_pGameModel->placeZone(ZoneType::Residential, row, column);
        break;
        case 1:
            m_pGameModel->placeZone(ZoneType::Residential, row, column);
        break;
        case 2:
            m_pGameModel->placeZone(ZoneType::Industrial, row, column);
        break;
        case 3:
            m_pGameModel->placeZone(ZoneType::Industrial, row, column);
        break;
        case 4:
            m_pGameModel->placeZone(ZoneType::Service, row, column);
        break;
        case 5:
            m_pGameModel->placeZone(ZoneType::Service, row, column);
        break;
        case 6:
            m_pGameModel->placeZone(ZoneType::Service, row, column);
        break;
    }
}

void GamePage::onRefreshboard()
{
    ui->tableWidget->clearContents();
    for(int y=0;y<m_pGameModel->getHeight();y++)
    {
        for(int x=0;x<m_pGameModel->getWidth();x++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem;

            //itt building at majd
            switch (m_pGameModel->zoneAt(x,y)) {
                case ZoneType::Industrial:
                    newItem->setIcon(QIcon(":/images/factory"));
                    break;
                case ZoneType::Residential:
                    newItem->setIcon(QIcon(":/images/house"));
                    break;
                case ZoneType::Service:
                    newItem->setIcon(QIcon(":/images/store"));
                    break;
                default:
                    newItem->setIcon(QIcon(":/images/free"));
                    break;
            }
            ui->tableWidget->setItem(x, y, newItem);

        }
    }


}

