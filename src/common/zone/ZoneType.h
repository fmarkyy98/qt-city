#pragma once

enum class ZoneType {
    Residential,
    Industrial,
    Service,
    Road,
    Forest,
    None,

    Count // Cool trick to get the count of the enum values.
};        // They must not be specified explicitly.

