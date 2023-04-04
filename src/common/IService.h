#pragma once

#include <memory>
#include <concepts>

#include <QObject>

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
    IService() : m_pMeta(std::make_unique<Meta_T>())
    {}

    Meta_T& meta() { return static_cast<Meta_T&>(*m_pMeta); }

private:
    std::unique_ptr<IServiceMeta> m_pMeta;
};
