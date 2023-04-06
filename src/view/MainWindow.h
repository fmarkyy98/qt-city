#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "GamePage.h"
#include "MenuPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showMenuPage();
    void showGamePage();

private:
    QStackedWidget *m_pStackedWidget;
    GamePage *m_pGamePage;
    MenuPage *m_pMenuPage;

};
