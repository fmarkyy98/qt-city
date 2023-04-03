#pragma once

#include <memory>
#include <concepts>

#include <QObject>

namespace common {
namespace details {

class IServiceMeta : public QObject {
    Q_OBJECT

signals:
};

}  // namespace details

template<typename Meta_T>
requires std::is_base_of_v<details::IServiceMeta, Meta_T>
class IService {
using IServiceMeta = details::IServiceMeta;

public:
    IService() : meta_(std::make_unique<Meta_T>())
    {}

    Meta_T& meta() { return static_cast<Meta_T&>(*meta_); }

private:
    std::unique_ptr<IServiceMeta> meta_;
};

}  // namespace common
