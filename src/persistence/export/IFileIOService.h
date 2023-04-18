#pragma once

#include "IService.h" 

#include <list>

class IFileIOServiceMeta : public details::IServiceMeta {
signals:
};

class IFileIOService : public IService<IFileIOServiceMeta>
{
public:
    virtual void save(const QString& path, const std::list<int>& dataList) const = 0;
    virtual std::list<int> load(const QString& path) const = 0;
};
