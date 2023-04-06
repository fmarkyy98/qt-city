#include "Mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_pStackedWidget = new QStackedWidget(this);
    m_pGamePage = new GamePage();
    m_pMenuPage = new MenuPage();
    m_pStackedWidget->addWidget(m_pGamePage);
    m_pStackedWidget->addWidget(m_pMenuPage);
    connect(m_pGamePage, &GamePage::showMenuPage, this, &MainWindow::showMenuPage);
    connect(m_pMenuPage, &MenuPage::showGamePage, this, &MainWindow::showGamePage);
    setCentralWidget(m_pStackedWidget);
    showMenuPage();
}

void MainWindow::showGamePage()
{
    m_pStackedWidget->setCurrentWidget(m_pGamePage);
}

void MainWindow::showMenuPage()
{
    m_pStackedWidget->setCurrentWidget(m_pMenuPage);
}
