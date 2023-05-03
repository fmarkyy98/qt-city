#include "WorkplaceBase.h"

WorkplaceBase::WorkplaceBase(QObject* parent)
    : BuildingBase(parent)
{}

std::list<int> WorkplaceBase::serialize() const {
    std::list<int> dataList;
    dataList.push_back(m_WorkerCount);

    dataList.merge(BuildingBase::serialize());

    return dataList;
}

void WorkplaceBase::deserialize(std::list<int>& dataList) {
    m_WorkerCount = dataList.front(); dataList.pop_front();

    BuildingBase::deserialize(dataList);
}

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
