#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "GamePage.h"
#include "MenuPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<IGameModel> model, QWidget *parent = nullptr);

private slots:
    void showMenuPage();
    void showGamePage();

private:
    QStackedWidget *m_pStackedWidget;
    GamePage *m_pGamePage;
    MenuPage *m_pMenuPage;

};
