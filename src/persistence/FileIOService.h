#pragma once

#include "IFileIOService.h"

class FileIOService
    : public QObject
    , public IFileIOService
{
    Q_OBJECT

    void save(const QString& path, const std::list<int>& dataList) const override;
    std::list<int> load(const QString& path) const override;
};
