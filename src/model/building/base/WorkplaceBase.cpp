#include "WorkplaceBase.h"

WorkplaceBase::WorkplaceBase(QObject* parent)
    : BuildingBase(parent)
{}

int WorkplaceBase::getWorkerCount() const {
    return m_WorkerCount;
}

WorkplaceBase& WorkplaceBase::setWorkerCount(int workerCount) {
    if (workerCount > getWorkerCapacity())
        throw std::invalid_argument("Worker limit exceeded :(");

    m_WorkerCount = workerCount;

    return *this;
}

int WorkplaceBase::addWorkerUntilLimit(int workerCountToAdd) {
    int remainder = 0;
    if (workerCountToAdd + getWorkerCount() > getWorkerCapacity())
        remainder = workerCountToAdd + getWorkerCount() - getWorkerCapacity();

    m_WorkerCount += workerCountToAdd - remainder;

    return remainder;
}

int WorkplaceBase::calculateMoneyProduced() const {
    return getProfitAfterWorker() * getWorkerCount();
}
