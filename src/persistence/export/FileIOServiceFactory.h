#pragma once

#include "IFileIOService.h"

#include <memory>

class FileIOServiceFactory final
{
public:
	static std::shared_ptr<IFileIOService> getFileIOService();
private:
	FileIOServiceFactory() = default;
	~FileIOServiceFactory() = default;
};