#include "MenuPage.h"
#include "ui_MenuPage.h"
#include <QScreen>


MenuPage::MenuPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPage)
{
    ui->setupUi(this);
    initConnections();
}

MenuPage::~MenuPage()
{
    delete ui;
}

void MenuPage::onNewGameButtonClicked()
{
    emit showGamePage();
}

void MenuPage::initConnections()
{
    connect(ui->newGameButton, &QPushButton::clicked, this, &MenuPage::onNewGameButtonClicked);
}

