#pragma once

#include <QtCore>

namespace qct {
	Q_NAMESPACE

    enum class BuildingType {
        Road,
        Forest,
        Residential,
        Factory,
        Store,
        Police,
        Stadium,
        None,

		Count // Cool trick to get the count of the enum values.
	};        // They must not be specified explicitly.
    Q_ENUM_NS(qct::BuildingType)

    enum class ZoneType {
        Radioactive = 0,
        None = 1,
        Residential = 2,
        Industrial = 4,
        Service = 8,
        NotNone = 14,
        All = 15
    };
    Q_ENUM_NS(qct::ZoneType)
}
