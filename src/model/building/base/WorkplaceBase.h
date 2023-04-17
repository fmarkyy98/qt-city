#pragma once

#include "BuildingBase.h"

class WorkplaceBase : public BuildingBase {
    Q_OBJECT
public:
    explicit WorkplaceBase(QObject* parent = nullptr);

    virtual int getWorkerCapacity() const = 0;
    virtual double getProfitAfterWorker() const = 0;

    int getWorkerCount() const;


    WorkplaceBase& setWorkerCount(int workerCount);

    int addWorkerUntilLimit(int workerCount);

    int calculateMoneyProduced() const;

protected:
    int m_WorkerCount = 0;
};
