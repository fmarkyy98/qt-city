#include "FileIOService.h"

using namespace persistence;

void FileIOService::save(const QString& path, const std::list<int>& dataList) const {
    std::runtime_error("Implement me!");
    return;
}

std::list<int> FileIOService::load(const QString& path) const {
    std::runtime_error("Implement me!");
    return {};
}
