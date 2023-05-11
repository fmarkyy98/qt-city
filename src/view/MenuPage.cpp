#include "MenuPage.h"
#include <QFileDialog>
#include <QMessageBox>
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

void MenuPage::onExitButtonClicked()
{
    QApplication::quit();
}

void MenuPage::onHelpButtonClicked()
{
    QMessageBox help;
    help.setText("A játékos egy jól körülhatárolt területet kap, amely négyzetalakú mezőkből áll."
                 " Ezen a területen építheti fel a játékos a saját városát és menedzselheti azt egy széles jogkörökkel bíró polgármesterként."
                 " A város leegyszerűsítve a különböző típusú zónákból (amelyeken a lakók automatikusan építkeznek), "
                 "a játékos által külön megépítendő kiszolgálóépületekből és az ezeket összekötő utakból áll."
                 " A játékos célja, hogy virágzó várost fejlesszen, ahol a polgárok boldogok és a költségvetés kiegyensúlyozott. "
                 "A kezdeti város építésére a játékos kap egy kezdőtőkét, azonban a további fejlesztésekhez a helyi adóbevételekre kell támaszkodnia. "
                 "A játékot valósidejűként kell elkészíteni, de a valósághoz képest természetesen az idő jóval gyorsabban fog telni. "
                 "A játék jelezze ki az időt(év,hónap,nap), és legyen lehetőség a játékot 3 különböző sebességben játszani, valamint a szüneteltetni is. "
                 "A kész játéknak minimálisan felülnézeti 2 dimenziós grafikával kell rendelkeznie, ahol az egyes mezőket statikus képek reprezentálják. "
                 "Többlet feladatként készíthető haladóbb grafikai megoldás is.");
    help.exec();
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
    connect(ui->exitGameButton, &QPushButton::clicked, this, &MenuPage::onExitButtonClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &MenuPage::onHelpButtonClicked);
}

