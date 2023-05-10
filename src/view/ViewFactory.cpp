#include "ViewFactory.h"
#include "IFileIOService.h"
#include "IService.h"
#include "persistence/FileIOService.h"
#include "GameModelFactory.h"

namespace internal {
	MainWindow *pMainWindow = nullptr;

	void createMainWindow()
	{
		if (!pMainWindow)
		{
			//TODO Factory to GameModel and FIleIOService
			std::shared_ptr<IGameModel> pModel = GameModelFactory::getGameModel();
			pMainWindow = new MainWindow(pModel);
		}
	}
}

MainWindow* ViewFactory::getMainWindow()
{
	internal::createMainWindow();
	return internal::pMainWindow;
}
