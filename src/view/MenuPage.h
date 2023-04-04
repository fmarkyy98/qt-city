#ifndef MENUPAGE_H
#define MENUPAGE_H

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
    void on_newGameButton_clicked();

private:
    Ui::MenuPage *ui;
};

#endif // MENUPAGE_H
