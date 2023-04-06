#pragma once

#include <QWidget>

namespace Ui {
class MenuPage;
}

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);
    ~MenuPage();

signals:
    void showGamePage();

private slots:
    void onNewGameButtonClicked();

private:
    void initConnections();

private:
    Ui::MenuPage *ui;
};
