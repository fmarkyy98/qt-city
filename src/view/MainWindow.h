#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "GamePage.h"
#include "MenuPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMenuPage();
    void showGamePage();

private:
    QStackedWidget *stackedWidget;
    GamePage *gamePage;
    MenuPage *menuPage;

};
#endif // MAINWINDOW_H
