#pragma once

#include "IGameModel.h"

#include <memory>

class GameModelFactory final
{
public:
	static std::shared_ptr<IGameModel> getGameModel();
private:
	GameModelFactory() = default;
	~GameModelFactory() = default;
};