#pragma once

#include <QObject>

#include "export/IFileIOService.h"

class FileIOService
    : public QObject
    , public IFileIOService
{
    Q_OBJECT

public:
    void save(const QString& path, const std::list<int>& dataList) const override;
    std::list<int> load(const QString& path) const override;
};
