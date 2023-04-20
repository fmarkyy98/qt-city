#include "FileIOService.h"

void FileIOService::save(const QString& path, const std::list<int>& dataList) const {
    throw std::runtime_error("Implement me!");
    return;
}

std::list<int> FileIOService::load(const QString& path) const {
    throw std::runtime_error("Implement me!");
    return {};
}
