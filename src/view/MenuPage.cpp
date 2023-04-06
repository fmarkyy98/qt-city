#include "MenuPage.h"
#include "QtWidgets/qboxlayout.h"
#include "ui_MenuPage.h"
#include <QScreen>


MenuPage::MenuPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPage)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout();
    int WINDOW_WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    int WINDOW_HEIGHT = (QGuiApplication::screens().at(0)->availableGeometry().height())-30;
    this->setMinimumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    layout->setContentsMargins(WINDOW_WIDTH/3, WINDOW_HEIGHT/4, WINDOW_WIDTH/3, WINDOW_HEIGHT/4);
    this->ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->ui->newGameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->ui->loadGameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->ui->exitGameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(this->ui->label);
    layout->addWidget(this->ui->newGameButton);
    layout->addWidget(this->ui->loadGameButton);
    layout->addWidget(this->ui->exitGameButton);
    this->setLayout(layout);
}

MenuPage::~MenuPage()
{
    delete ui;
}

void MenuPage::on_newGameButton_clicked()
{
    emit showGamePage();
}

