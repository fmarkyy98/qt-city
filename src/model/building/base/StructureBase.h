#pragma once

#include <QObject>

#include "../../export/Enums.h"

#define DECLARE_STRUCTURE_BASE_MEMBERS       \
qct::BuildingType getType() const override;  \
qct::ZoneType getCompatibleZone() const override;

#define DEFINE_STRUCTURE_BASE_MEMBERS(CLASS)      \
qct::BuildingType CLASS::getType() const {        \
        return s_Type;                            \
}                                                 \
qct::ZoneType CLASS::getCompatibleZone() const {  \
        return s_Zone;                            \
}

class StructureBase : public QObject {
    Q_OBJECT
public:
    explicit StructureBase(QObject* parent = nullptr);

    virtual qct::BuildingType getType() const = 0;

    bool canBuildOnZone(const qct::ZoneType& zoneType) const;

protected:
    virtual qct::ZoneType getCompatibleZone() const = 0;
};
