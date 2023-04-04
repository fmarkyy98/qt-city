#ifndef WORKPLACEBASE_H
#define WORKPLACEBASE_H

#include <QObject>

class WorkplaceBase : public QObject
{
    Q_OBJECT
public:
    explicit WorkplaceBase(QObject *parent = nullptr);

signals:

};

#endif // WORKPLACEBASE_H
