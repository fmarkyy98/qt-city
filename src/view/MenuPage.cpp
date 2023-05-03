#include "MenuPage.h"
#include "ui_MenuPage.h"
#include <QScreen>


MenuPage::MenuPage(std::shared_ptr<IGameModel> model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPage)
    , m_pGameModel(model)
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
    m_pGameModel->newGame();
}

void MenuPage::initConnections()
{
    connect(ui->newGameButton, &QPushButton::clicked, this, &MenuPage::onNewGameButtonClicked);
}

