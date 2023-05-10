#include "MenuPage.h"
#include <QFileDialog>
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

void MenuPage::onLoadGameButtonClicked()
{
    emit showGamePage();
    QString filename = QFileDialog::getOpenFileName();
    qDebug() << filename;
    m_pGameModel->load(filename);

}

void MenuPage::initConnections()
{
    connect(ui->newGameButton, &QPushButton::clicked, this, &MenuPage::onNewGameButtonClicked);
    connect(ui->loadGameButton, &QPushButton::clicked, this, &MenuPage::onLoadGameButtonClicked);
}

