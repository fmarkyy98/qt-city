#pragma once

#include <QWidget>
#include "IGameModel.h"
#include "GamePage.h"

namespace Ui {
class MenuPage;
}

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(std::shared_ptr<IGameModel> model, QWidget *parent = nullptr);
    ~MenuPage();

signals:
    void showGamePage();

private slots:
    void onNewGameButtonClicked();

private:
    void initConnections();
    void initGame();
    void newGame();
    void load();

private:
    Ui::MenuPage *ui;
    std::shared_ptr<IGameModel> m_pGameModel;
};
