#pragma once

#include <QtCore>

namespace QtCity {
	Q_NAMESPACE

	enum class BuildingType {
		Residential,
		Factory,
		Police,
		None,

		Count // Cool trick to get the count of the enum values.
	};        // They must not be specified explicitly.
	Q_ENUM_NS(BuildingType)

	enum class ZoneType {
		Residential,
		Industrial,
		Service,
		None,

		Count // Cool trick to get the count of the enum values.
	};        // They must not be specified explicitly.
	Q_ENUM_NS(ZoneType)
}