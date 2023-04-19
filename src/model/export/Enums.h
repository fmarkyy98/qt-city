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
		Residential,
		Industrial,
		Service,
		None,

		Count // Cool trick to get the count of the enum values.
	};        // They must not be specified explicitly.
    Q_ENUM_NS(qct::ZoneType)
}
