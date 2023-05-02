#include "StructureBase.h"

StructureBase::StructureBase(QObject* parent)
    : QObject(parent)
{}

std::list<int> StructureBase::serialize() const {
    return {};
}

bool StructureBase::canBuildOnZone(const qct::ZoneType& zoneType) const {
    return static_cast<int>(zoneType) & static_cast<int>(getCompatibleZone());
}
