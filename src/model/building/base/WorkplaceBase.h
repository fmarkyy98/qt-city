#pragma once

#include "BuildingBase.h"

#define DECLARE_WORKPLACE_BASE_MEMBERS   \
int getWorkerCapacity() const override;  \
double getProfitAfterWorker() const override;

#define DEFINE_WORKPLACE_BASE_MEMBERS(CLASS)          \
int CLASS::getWorkerCapacity() const {                \
    return s_WorkerCapacityByLevel[m_BuildingLevel];  \
}                                                     \
double CLASS::getProfitAfterWorker() const {          \
    return s_ProfitByLevel[m_BuildingLevel];          \
}

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
