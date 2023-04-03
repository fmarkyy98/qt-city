#pragma once

#include <list>

#include <QObject>

#include "../common/IService.h" // TODO normális útvonalat megadni.

namespace persistence {

class IFileIOServiceMeta : public common::details::IServiceMeta {
signals:
};

class IFileIOService : public common::IService<IFileIOServiceMeta>
{
public:
    virtual void save(const QString& path, const std::list<int>& dataList) const = 0;
    virtual std::list<int> load(const QString& path) const = 0;
};

}  // namespace persistence
