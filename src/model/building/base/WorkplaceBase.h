#pragma once

#include "BuildingBase.h"

class WorkplaceBase : public BuildingBase {
    Q_OBJECT
public:
    explicit WorkplaceBase(int workerCapacity,
                           int workerCount,
                           double profitAfterWorker,
                           QObject* parent = nullptr);

    int getWorkerCapacity() const;
    int getWorkerCount() const;
    // double getProfitAfterWorker() const; Not sure if we need this.

    WorkplaceBase& setWorkerCapacity(int workerCapacity);
    WorkplaceBase& setWorkerCount(int workerCount);
    WorkplaceBase& setProfitAfterWorker(double profitAfterWorker);

    int addWorkerUntilLimit(int workerCount);
    int calculateMoneyProduced() const;

protected:
    int m_WorkerCapacity;
    int m_WorkerCount;
    double m_ProfitAfterWorker;
};
