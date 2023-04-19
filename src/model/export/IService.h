#pragma once

#include <memory>
#include <concepts>

#include <QObject>

namespace details {
    Q_NAMESPACE

        class IServiceMeta : public QObject {
        Q_OBJECT

        signals:
    };

}  // namespace details

template<typename Meta_T>
requires std::is_base_of_v<details::IServiceMeta, Meta_T>
class IService {
public:
    using Meta = Meta_T;

    IService() : m_pMeta(std::make_unique<Meta>())
    {}

    Meta* meta() { return static_cast<Meta*>(m_pMeta.get()); }

private:
    std::unique_ptr<details::IServiceMeta> m_pMeta;
};
