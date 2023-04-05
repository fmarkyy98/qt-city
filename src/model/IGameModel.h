#pragma once

#include "../common/IService.h" // TODO normális útvonalat megadni.

class IGameModelMeta : public details::IServiceMeta {
signals:
    void onMoneyChanged(int money);
    void onBoardChanged();
    void onZonesChanged();
};

class IGameModel : public IService<IGameModelMeta>
{
public:
    virtual zoneAt(std::pair<int,int> position) const = 0;
    virtual void save(const QString& path) const = 0;
    virtual void load(const QString& path) = 0;
};
