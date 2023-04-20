#include "StructureBase.h"

StructureBase::StructureBase(QObject* parent)
    : QObject(parent)
{}

bool StructureBase::canBuildOnZone(const qct::ZoneType& zoneType) const {
    return static_cast<int>(zoneType) & static_cast<int>(getCompatibleZone());
}
