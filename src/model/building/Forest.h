#pragma once

#include "base/StructureBase.h"

class Forest : public StructureBase {
    Q_OBJECT
public:
    explicit Forest(QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Forest;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::All;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
};
