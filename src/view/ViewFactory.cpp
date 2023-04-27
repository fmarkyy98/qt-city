#include "ViewFactory.h"
#include "IFileIOService.h"
#include "IService.h"
#include "persistence/FileIOService.h"
#include "model/GameModel.h"

namespace internal {
	MainWindow *pMainWindow = nullptr;

	void createMainWindow()
	{
		if (!pMainWindow)
		{
			//TODO Factory to GameModel and FIleIOService
			std::shared_ptr<IFileIOService> pFileIOService = std::make_shared<FileIOService>();
			std::shared_ptr<IGameModel> pModel = std::make_shared<GameModel>(pFileIOService);
			pMainWindow = new MainWindow(pModel);
		}
	}
}

MainWindow* ViewFactory::getMainWindow()
{
	internal::createMainWindow();
	return internal::pMainWindow;
}
