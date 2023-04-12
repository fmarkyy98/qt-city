#include "view/MainWindow.h"
#include "persistence/FileIOService.h"
#include "model/GameModel.h"
#include <memory>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<IFileIOService> fileIOService = std::make_shared<FileIOService>();
    std::shared_ptr<IGameModel> model = std::make_shared<GameModel>(fileIOService);
    MainWindow w(model);
    w.showMaximized();
    return a.exec();
}
