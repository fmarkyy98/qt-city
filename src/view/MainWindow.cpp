#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    gamePage = new GamePage(this);
    menuPage = new MenuPage(this);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(menuPage);
    connect(gamePage, &GamePage::showMenuPage, this, &MainWindow::showMenuPage);
    connect(menuPage, &MenuPage::showGamePage, this, &MainWindow::showGamePage);
    setCentralWidget(stackedWidget);
    showMenuPage();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::showGamePage()
{
    stackedWidget->setCurrentWidget(gamePage);
}

void MainWindow::showMenuPage()
{
    stackedWidget->setCurrentWidget(menuPage);
}
