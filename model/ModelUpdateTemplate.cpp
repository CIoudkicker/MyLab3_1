#include "ModelUpdateTemplate.h"

ModelUpdateTemplate::ModelUpdateTemplate(QObject *parent) : QAbstractTableModel(parent)
{
    map = DataForTable();
    context = new Context_CalculateSize;
}

void ModelUpdateTemplate::UpdateAndNotify(QString path)
{
    this->beginResetModel();
    this->RequiredOperations1(path);
    map = context->getMap();
    this->Notify();
    this->endResetModel();
}

void ModelUpdateTemplate::UpdateAndNotify(ICalculateSize *strat, QString path)
{
    this->beginResetModel();
    this->RequiredOperations1(strat, path);
    map = context->getMap();
    this->Notify();
    this->endResetModel();
}

void ModelUpdateTemplate::Attach(IObserver *observer)
{
    list_observer_.push_back(observer);
}

void ModelUpdateTemplate::Detach(IObserver *observer)
{
    list_observer_.remove(observer);
}

void ModelUpdateTemplate::Notify()
{
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    while (iterator != list_observer_.end()) {
        (*iterator)->Update(map);
        ++iterator;
    }
}
