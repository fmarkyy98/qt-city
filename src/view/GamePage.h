#pragma once

#include <QWidget>

namespace Ui {
class GamePage;
}

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

signals:
    void showMenuPage();

private slots:
    void onSaveButtonClicked();

    void onSettingsButtonClicked();

    void onSlowerButtonClicked();

    void onPauseButtonClicked();

    void onFasterButtonClicked();

    void onExitButtonClicked();

    void onMenuButtonClicked();

private:
    void initConnections();
private:
    Ui::GamePage *ui;

};

