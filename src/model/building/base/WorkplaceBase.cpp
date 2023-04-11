#include "WorkplaceBase.h"

WorkplaceBase::WorkplaceBase(int workerCapacity,
                             int workerCount,
                             double profitAfterWorker,
                             QObject* parent)
    : BuildingBase(parent)
    , m_WorkerCapacity(workerCapacity)
    , m_WorkerCount(workerCount)
    , m_ProfitAfterWorker(profitAfterWorker)
{}

int WorkplaceBase::getWorkerCapacity() const {
    return m_WorkerCapacity;
}

int WorkplaceBase::getWorkerCount() const {
    return m_WorkerCount;
}

/* Not sure if we need this.
double WorkplaceBase::getProfitAfterWorker() const {
    return m_ProfitAfterWorker;
}
*/

WorkplaceBase& WorkplaceBase::setWorkerCapacity(int workerCapacity) {
    m_WorkerCapacity = workerCapacity;

    return *this;
}

WorkplaceBase& WorkplaceBase::setWorkerCount(int workerCount) {
    if (workerCount > m_WorkerCapacity)
        throw std::invalid_argument("Worker limit exceeded :(");

    m_WorkerCount = workerCount;

    return *this;
}

WorkplaceBase& WorkplaceBase::setProfitAfterWorker(double profitAfterWorker) {
    m_ProfitAfterWorker = profitAfterWorker;

    return *this;
}

int WorkplaceBase::addWorkerUntilLimit(int workerCountToAdd) {
    int remainder = 0;
    if (workerCountToAdd + m_WorkerCount > m_WorkerCapacity)
        remainder = workerCountToAdd + m_WorkerCount - m_WorkerCapacity;

    m_WorkerCount += workerCountToAdd - remainder;

    return remainder;
}

int WorkplaceBase::calculateMoneyProduced() const {
    return m_ProfitAfterWorker * m_WorkerCount;
}
