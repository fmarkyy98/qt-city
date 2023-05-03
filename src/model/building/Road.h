#pragma once

#include "base/StructureBase.h"

class Road : public StructureBase {
    Q_OBJECT
public:
    explicit Road(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Road;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::All;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
};
