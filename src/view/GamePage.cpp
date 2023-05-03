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


void GamePage::onSlowerButtonClicked()
{
    if(!isGamePaused){
        switch(speedLevel){
        case 2000:
            break;
        case 1000:
            speedLevel=2000;
            timer.start(2000);
            ui->slowerButton->setEnabled(false);
            break;
        case 500:
            timer.start(1000);
            speedLevel=1;
            ui->fasterButton->setEnabled(true);
            break;
        }
    }
}


void GamePage::onPauseButtonClicked()
{
    if (isGamePaused) {
        timer.start(speedLevel);
        isGamePaused=false;
        ui->pauseButton->setText("⏸");
    } else {
        timer.stop();
        isGamePaused=true;
        ui->pauseButton->setText("►");
    }
}


void GamePage::onFasterButtonClicked()
{
    if(!isGamePaused){
        switch(speedLevel){
        case 2000:
            speedLevel=1000;
            ui->slowerButton->setEnabled(true);
            timer.start(1000);
            break;
        case 1000:
            speedLevel=500;
            timer.start(500);
            ui->fasterButton->setEnabled(false);
            break;
        case 500:
            break;
        }
    }
}


void GamePage::onExitButtonClicked()
{
    QApplication::quit();
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
    //connect(ui->settingsButton, &QPushButton::clicked, this, &GamePage::onSettingsButtonClicked);
    connect(ui->tableWidget_2, &QTableWidget::cellClicked, this, &GamePage::onTableWidget2Clicked);
    connect(ui->tableWidget_3, &QTableWidget::cellClicked, this, &GamePage::onTableWidget3Clicked);
    connect(&timer, &QTimer::timeout, this, &GamePage::onTimeElapsed);
    connect(m_pGameModel->meta(), &IGameModel::Meta::boardChanged, this, &GamePage::onRefreshboard);
    connect(m_pGameModel->meta(), &IGameModel::Meta::moneyChanged, this, &GamePage::onMoneyChanaged);
    connect(m_pGameModel->meta(), &IGameModel::Meta::dateChanged, this, &GamePage::onDateChanged);

}

void GamePage::onTimeElapsed()
{
    m_pGameModel->advanceSimulation();
}

/*void GamePage::onBoardChanged()
{
    //TODO
}*/

void GamePage::onZonesChanged()
{
    //TODO
}

void GamePage::onMoneyChanaged(int money)
{
    ui->label_3->setText("Pemz: " + QString::number(money) + " csengőPengő");
}

void GamePage::onDateChanged(const QDate& date)
{
    ui->label_2->setText("Time: "+date.toString("yyyy.MM.dd"));
}

void GamePage::newGame()
{
    isGamePaused = false;
    speedLevel=1000;
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


    for(int i=1; i<8; i++)
    {
        ui->tableWidget_2->item(0,i)->setData(Qt::DecorationRole, QPixmap(this->images[i-1]));
    }
    ui->tableWidget_2->item(0,8)->setText("Choose a building or Zone!");
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableWidget,&QAbstractItemView::clicked,this,[this](const QModelIndex& idx)->void{
        rowInd=idx.row();
        columnInd=idx.column();
        auto structure = m_pGameModel->structureAt(rowInd, columnInd);
        if(structure ==nullptr) {
            stackedWidget->setCurrentWidget(ui->tableWidget_2);
        } else {
            pixMap=getPixMap(structure);

            ui->tableWidget_3->item(0,0)->setData(Qt::DecorationRole, pixMap);
            ui->tableWidget_3->item(0,1)->setText(info);
            stackedWidget->setCurrentWidget(ui->tableWidget_3);
        }
        qDebug() << "Clicked: " << idx.row()<<","<<idx.column();
        qDebug() << "Saved: " << rowInd<<","<<columnInd;
    });

    timer.start(1000);
}

QPixmap GamePage::getPixMap(const StructureBase *structure, std::optional<std::pair<int,int>> coordinates){
    auto type = structure->getType();
    auto workPlace = dynamic_cast<const WorkplaceBase*>(structure);
    switch (type) {
    case qct::BuildingType::Road: {
        info="Road";
        priceInfo="Road\nPrice:"+QString::number(m_pGameModel->getCostOfBuildingBuilding());

        return QPixmap(":/images/road");
    } break;
    case qct::BuildingType::Store: {
        capacity=workPlace->getWorkerCapacity();
        peopleCount=workPlace->getWorkerCount();
        info="Store\nCount of the people: "+QString::number(peopleCount)+"\nCapacity: "+QString::number(capacity);
        return QPixmap(":/images/store");
    } break;
    case qct::BuildingType::Stadium: {
        capacity=workPlace->getWorkerCapacity();
        peopleCount=workPlace->getWorkerCount();
        info="Stadium\nCount of the people: "+QString::number(peopleCount)+"\nCapacity: "+QString::number(capacity);
        if(coordinates==std::nullopt)
            return QPixmap(":/images/stadium");
        if(m_pGameModel->structureAt(coordinates->first-1, coordinates->second)!=structure && m_pGameModel->structureAt(coordinates->first, coordinates->second-1)!=structure)
            return QPixmap(":/images/stadium1");
        else if(m_pGameModel->structureAt(coordinates->first-1, coordinates->second)==structure && m_pGameModel->structureAt(coordinates->first, coordinates->second-1)!=structure)
            return QPixmap(":/images/stadium3");
        else if(m_pGameModel->structureAt(coordinates->first-1, coordinates->second-1)!=structure && m_pGameModel->structureAt(coordinates->first, coordinates->second-1)==structure)
            return QPixmap(":/images/stadium2");
        else if(m_pGameModel->structureAt(coordinates->first-1, coordinates->second)==structure && m_pGameModel->structureAt(coordinates->first, coordinates->second-1)==structure)
            return QPixmap(":/images/stadium4");
    } break;
    case qct::BuildingType::Forest: {
        info="Forest";
        return QPixmap(":/images/forest");
    } break;

    case qct::BuildingType::Factory: {
        capacity=workPlace->getWorkerCapacity();
        peopleCount=workPlace->getWorkerCount();
        info="Factory\nCount of the people: "+QString::number(peopleCount)+"\nCapacity: "+QString::number(capacity);
        return QPixmap(":/images/factory");
    } break;
    case qct::BuildingType::Residential: {
        auto house = dynamic_cast<const ResidentialBuilding*>(structure);
        capacity=house->getCapacity();
        peopleCount=house->getInhabitantCount();
        house->getLevel();
        info="Residential Building\nCount of the people: "+QString::number(peopleCount)+"\nCapacity: "+QString::number(capacity);
        if(house->isBuildInProgress()) {
            if(house->getLevel()==0)
                return QPixmap(":/images/house_construct");
            else if (house->getLevel()==1)
                return QPixmap(":/images/house2_construct");
            else
                return QPixmap(":/images/house3_construct");
        } else {
            if(house->getLevel()==1)
                return QPixmap(":/images/house");
            else if (house->getLevel()==2)
                return QPixmap(":/images/house2");
            else
                return QPixmap(":/images/house3");
        }

    } break;
    case qct::BuildingType::Police: {
        capacity=workPlace->getWorkerCapacity();
        peopleCount=workPlace->getWorkerCount();
        info="Police\nCount of the people: "+QString::number(peopleCount)+"\nCapacity: "+QString::number(capacity);
        return QPixmap(":/images/police");
    } break;

    default: {
        return QPixmap(":/images/free");
    } break;
    }
}

void GamePage::onTableWidget2Clicked(int row, int column)
{
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
                ui->tableWidget_2->item(0,8)->setText(
                            "Road\nPrice:"+
                            QString::number(m_pGameModel->getCostOfBuildingBuilding())
                            );
            }
        break;
        case 2:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Residential;
                ui->tableWidget_2->item(0,8)->setText(
                            "House\nPrice: "+
                             QString::number(m_pGameModel->getCostOfBuildingBuilding())+
                             "\nCapacity: "+
                             QString::number(ResidentialBuilding::capacity));
            } else {
                chosenZoneType=qct::ZoneType::Residential;
                placingBuilding=false;
                ui->tableWidget_2->item(0,8)->setText(
                            "Residential Zone\nPrice: "+
                             QString::number(m_pGameModel->getCostOfPlacingZone()));
            }
        break;
        case 3:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Factory;
                ui->tableWidget_2->item(0,8)->setText(
                            "Factory\nPrice: "+
                             QString::number(m_pGameModel->getCostOfBuildingBuilding())+
                             "\nCapacity: "+
                             QString::number(Factory::workerCapacity));
            } else {
                chosenZoneType=qct::ZoneType::Industrial;
                ui->tableWidget_2->item(0,8)->setText(
                            "Industrial Zone\nPrice: "+
                             QString::number(m_pGameModel->getCostOfPlacingZone()));
                placingBuilding=false;
            }
        break;
        case 4:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Store;
                ui->tableWidget_2->item(0,8)->setText(
                            "Store\nPrice:"+
                            QString::number(m_pGameModel->getCostOfBuildingBuilding())+
                            "\nCapacity: "+
                            QString::number(Store::workerCapacity));
            } else {
                chosenZoneType=qct::ZoneType::Service;
                ui->tableWidget_2->item(0,8)->setText(
                            "Service Zone\nPrice: "+
                             QString::number(m_pGameModel->getCostOfPlacingZone()));
                placingBuilding=false;
            }
        break;
        case 5:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Police;
                ui->tableWidget_2->item(0,8)->setText(
                            "Police\nPrice:"+
                            QString::number(m_pGameModel->getCostOfBuildingBuilding())+
                            "\nCapacity: "+
                            QString::number(Police::workerCapacity));

            } else {
                chosenZoneType=qct::ZoneType::Service;
                placingBuilding=false;
                ui->tableWidget_2->item(0,8)->setText(
                            "Service Zone\nPrice: "+
                             QString::number(m_pGameModel->getCostOfPlacingZone()));
            }
        break;
        case 6:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Stadium;
                ui->tableWidget_2->item(0,8)->setText(
                            "Stadion\nPrice:"+
                            QString::number(m_pGameModel->getCostOfBuildingBuilding())+
                            "\nCapacity: "+
                            QString::number(Stadium::workerCapacity));
            } else {
                chosenZoneType=qct::ZoneType::Service;
                placingBuilding=false;
                ui->tableWidget_2->item(0,8)->setText(
                            "Service Zone\nPrice: "+
                             QString::number(m_pGameModel->getCostOfPlacingZone()));
            }
        break;
        case 7:
            if (row == 0) {
                placingBuilding=true;
                chosenBuildingType=qct::BuildingType::Forest;
                ui->tableWidget_2->item(0,8)->setText(
                            "Forest\nPrice:"+
                            QString::number(m_pGameModel->getCostOfBuildingBuilding())
                            );
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
            switch (m_pGameModel->zoneAt(x,y)) {
                case qct::ZoneType::Industrial:
                    ui->tableWidget->item(x,y)->setBackground(QColor(113, 10, 0));
                    break;
                case qct::ZoneType::Service:
                    ui->tableWidget->item(x,y)->setBackground(QColor(30, 50, 50));
                    break;
                case qct::ZoneType::Residential:
                    ui->tableWidget->item(x,y)->setBackground(QColor(200, 120, 0));
                    break;
                case qct::ZoneType::None:
                    break;
            }
            auto structure = m_pGameModel->structureAt(x, y);
            if (structure == nullptr)
                continue;

            pixMap=getPixMap(structure, std::make_pair( x, y ));
            QLabel* label = new QLabel();
            QRect viewportRect = ui->tableWidget->viewport()->rect();
            int cellWidth = viewportRect.width() / ui->tableWidget->columnCount();
            int cellHeight = viewportRect.height() / ui->tableWidget->rowCount();
            pixMap = pixMap.scaled(cellWidth, cellHeight, Qt::IgnoreAspectRatio);
            label->setPixmap(pixMap);
            label->setFixedSize(pixMap.size());
            ui->tableWidget->setCellWidget(x, y, label);
            ui->tableWidget->item(x, y)->setSizeHint(pixMap.size());
            ui->tableWidget->item(x, y)->setFlags(ui->tableWidget->item(x, y)->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
}

void GamePage::onTableWidget3Clicked(int row, int column)
{
    QMessageBox messageBox;
    qDebug() << "Column:: " << column;
    switch(column)
    {
        case 0:
        break;
        case 1:
        break;
        case 2:
            //TODO
        break;
        case 3:
            //m_pGameModel->evolveBuilding(m_pGameModel->structureAt(rowInd, columnInd));
        break;
    }
}

