#include "GameModelFactory.h"
#include "IFileIOService.h"
#include "IService.h"
#include "FileIOServiceFactory.h"
#include "GameModel.h"

namespace {
	static std::shared_ptr<IGameModel> pModel = nullptr;

	void createGameModel()
	{
		if (!pModel)
		{
			pModel = std::make_shared<GameModel>(FileIOServiceFactory::getFileIOService());
		}
	}
}

std::shared_ptr<IGameModel> GameModelFactory::getGameModel()
{
	createGameModel();
	return pModel;
}