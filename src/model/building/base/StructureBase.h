#pragma once

#include <QObject>

#include "../../export/Enums.h"

#define DECLARE_STRUCTURE_BASE_MEMBERS             \
qct::BuildingType getType() const override;        \
qct::ZoneType getCompatibleZone() const override;  \
std::pair<int, int> getSize() const override;      \
int getWidth() const override;                     \
int getHeight() const override;

#define DEFINE_STRUCTURE_BASE_MEMBERS(CLASS)      \
qct::BuildingType CLASS::getType() const {        \
        return s_Type;                            \
}                                                 \
qct::ZoneType CLASS::getCompatibleZone() const {  \
        return s_Zone;                            \
}                                                 \
std::pair<int, int> CLASS::getSize() const {      \
    return {s_Width, s_Height};                   \
}                                                 \
int CLASS::getWidth() const {                     \
    return s_Width;                               \
}                                                 \
int CLASS::getHeight() const {                    \
    return s_Height;                              \
}

class StructureBase : public QObject {
    Q_OBJECT
public:
    explicit StructureBase(QObject* parent = nullptr);

    virtual qct::BuildingType getType() const = 0;
    virtual std::pair<int, int> getSize() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    bool canBuildOnZone(const qct::ZoneType& zoneType) const;

protected:
    virtual qct::ZoneType getCompatibleZone() const = 0;
};
