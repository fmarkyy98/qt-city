#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<IGameModel> model, QWidget *parent)
    : QMainWindow(parent)
{
    m_pStackedWidget = new QStackedWidget(this);
    m_pGamePage = new GamePage(model);
    m_pMenuPage = new MenuPage(model);
    m_pStackedWidget->addWidget(m_pGamePage);
    m_pStackedWidget->addWidget(m_pMenuPage);
    connect(m_pGamePage, &GamePage::showMenuPage, this, &MainWindow::showMenuPage);
    connect(m_pMenuPage, &MenuPage::showGamePage, this, &MainWindow::showGamePage);
    setCentralWidget(m_pStackedWidget);
    setStyleSheet("MainWindow {border-image: url(:/images/background) 0 0 0 0 stretch stretch;}");
    showMenuPage();
}

void MainWindow::showGamePage()
{
    m_pStackedWidget->setCurrentWidget(m_pGamePage);
    m_pGamePage->newGame();
}

void MainWindow::showMenuPage()
{
    m_pStackedWidget->setCurrentWidget(m_pMenuPage);
}
