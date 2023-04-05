#pragma once

#include <QObject>

#include "IGameModel.h"

class GameModel
    : public QObject
    , public IGameModel
{
    Q_OBJECT

    void save(const QString& path) const override;
    void load(const QString& path) override;
};
