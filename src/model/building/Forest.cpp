#include "Forest.h"

Forest::Forest(QDate builtYear,QObject* parent)
    : StructureBase(parent)
    , m_builtYear(builtYear)
{}

DEFINE_STRUCTURE_BASE_MEMBERS(Forest)
