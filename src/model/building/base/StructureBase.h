#pragma once

#include <QObject>

#include "../../export/Enums.h"

#define DECLARE_STRUCTURE_BASE_MEMBERS  \
qct::BuildingType getType() const override;

#define DEFINE_STRUCTURE_BASE_MEMBERS(CLASS)  \
qct::BuildingType CLASS::getType() const {    \
        return s_Type;                        \
}

class StructureBase : public QObject {
    Q_OBJECT
public:
    explicit StructureBase(QObject* parent = nullptr);

    virtual qct::BuildingType getType() const = 0;
};
