#include "CalculateSize_TableModel.h"

CalculateSize_TableModel::CalculateSize_TableModel(QObject *parent)
    : ModelUpdateTemplate(parent) { }

CalculateSize_TableModel::~CalculateSize_TableModel()
{
    delete context;
}

int CalculateSize_TableModel::rowCount(const QModelIndex &) const
{
    return map.count();
}

int CalculateSize_TableModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant CalculateSize_TableModel::data(const QModelIndex &index, int role) const
{

    switch (role) {
    case Qt::DisplayRole:
        DataForTable::const_iterator i = map.begin();
        i += index.row();
        if (map.empty()) {
            return QVariant();
            ;
        }

        if (i.value().count() > 1) {
            QString size = QString::number(i.value()[0], 'g', 20);
            QString procent = QString::number(i.value()[1]);
            if (index.column() == 0)
                return i.key();
            if (index.column() == 1)
                return size;
            if (index.column() == 2) {
                if (size != 0 && i.value()[1] == 0) {
                    return "< 0.01";
                } else {
                    return QString::number(i.value()[1]);
                }
            }
            return i.key() + " size " + size + " procent " + procent;
        } else if (i.value().count() == 1) {
            QString size = QString::number(i.value()[0], 'g', 20);
            if (index.column() == 0)
                return "Total Size";
            if (index.column() == 1)
                return size;
            if (index.column() == 2)
                return "";
        }
        break;
    }
    return QVariant();
}

QVariant CalculateSize_TableModel::headerData(int section, Qt::Orientation orientation,
                                              int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Name");
        case 1:
            return QString("Size");
        case 2:
            return QString("Procent");
        }
    }
    return QVariant();
}

void CalculateSize_TableModel::RequiredOperations1(QString path)
{
    context->changeStrat(context->getStrat(), path);
}

void CalculateSize_TableModel::RequiredOperations1(ICalculateSize *strat, QString path)
{
    context->changeStrat(strat, path);
}

void CalculateSize_TableModel::append(QString path)
{
    UpdateAndNotify(context->getStrat(), path);
}

void CalculateSize_TableModel::changeStrat(ICalculateSize *strat, QString path)
{
    UpdateAndNotify(strat, path);
}
