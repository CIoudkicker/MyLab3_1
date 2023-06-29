#ifndef MODELSAMPEL_H
#define MODELSAMPEL_H

#include <QAbstractTableModel>

#include "ICalculateSize.h"
#include "IObserver.h"
#include "Context_CalculateSize.h"

class ModelUpdateTemplate : public QAbstractTableModel, public ISubject
{
public:
    ModelUpdateTemplate(QObject *parent);

    void UpdateAndNotify(QString path);

    void UpdateAndNotify(ICalculateSize *strat, QString path);

    void Attach(IObserver *observer) override;
    void Detach(IObserver *observer) override;
    void Notify() override;

    DataForTable getMap() { return map; }

protected:
    DataForTable map;
    Context_CalculateSize *context;
    std::list<IObserver *> list_observer_;
    virtual void RequiredOperations1(QString path) = 0;
    virtual void RequiredOperations1(ICalculateSize *strat, QString path) = 0;
};

#endif // MODELSAMPEL_H
