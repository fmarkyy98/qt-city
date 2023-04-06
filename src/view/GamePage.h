#ifndef GAMEPAGE_H
#define GAMEPAGE_H

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

    void on_menuButton_clicked();

private:
    Ui::GamePage *ui;
};

#endif // GAMEPAGE_H
