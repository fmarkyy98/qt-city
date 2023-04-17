#include "Factory.h"

Factory::Factory(QObject* parent)
    : WorkplaceBase(parent)
{}

BuildingType Factory::getType() const {
    return s_Type;
}

ZoneType Factory::getCompatibleZone() const {
    return s_Zone;
}

std::pair<int, int> Factory::getSize() const {
    return {s_Width, s_Height};
}

int Factory::getWidth() const {
    return s_Width;
}

int Factory::getHeight() const {
    return s_Height;
}

int Factory::getWorkerCapacity() const {
    return s_WorkerCapacityByLevel[m_BuildingLevel];
}

double Factory::getProfitAfterWorker() const {
    return s_ProfitByLevel[m_BuildingLevel];
}

void Factory::evolveSpecificBuildingImpl() {

}
