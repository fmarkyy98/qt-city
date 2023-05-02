#include "view/MainWindow.h"
#include "IFileIOService.h"
#include "IService.h"
#include "persistence/FileIOService.h"
#include "model/GameModel.h"
#include "ViewFactory.h"

#include <memory>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* pWindow = ViewFactory::getMainWindow();
    
    pWindow->showMaximized();
    return a.exec();
}
