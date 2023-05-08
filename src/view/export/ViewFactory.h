#pragma once

#include "../MainWindow.h"

#include <memory>

class ViewFactory final
{
public:
	static MainWindow* getMainWindow();
private:
	ViewFactory() = default;
	~ViewFactory() = default;
};