#pragma once

#include "base/StructureBase.h"
#include <QDate>

class Forest : public StructureBase {
    Q_OBJECT
public:
    explicit Forest(QDate builtYear, QObject* parent = nullptr);

    DECLARE_STRUCTURE_BASE_MEMBERS

public:
    QDate getBuiltYear() const {return m_builtYear;}

private:
    const QDate m_builtYear;

private:
    static constexpr qct::BuildingType s_Type = qct::BuildingType::Forest;
    static constexpr qct::ZoneType s_Zone = qct::ZoneType::All;
    static constexpr int s_Width = 1;
    static constexpr int s_Height = 1;
};
