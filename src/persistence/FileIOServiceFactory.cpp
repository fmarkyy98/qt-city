#include "FileIOServiceFactory.h"

#include "IFileIOService.h"
#include "IService.h"
#include "FileIOService.h"


namespace {
	static std::shared_ptr<IFileIOService> pFile = nullptr;

	void createFileIOService()
	{
		if (!pFile)
		{
			pFile = std::make_shared<FileIOService>();
		}
	}
}

std::shared_ptr<IFileIOService> FileIOServiceFactory::getFileIOService()
{
	createFileIOService();
	return pFile;
}