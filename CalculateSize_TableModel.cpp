#include "CalculateSize_TableModel.h"

CalculateSize_TableModel::CalculateSize_TableModel(QObject *parent):
    QAbstractTableModel(parent)
{

}


int CalculateSize_TableModel::rowCount(const QModelIndex &)const {
    return 1;
}


int CalculateSize_TableModel::columnCount(const QModelIndex &)const {
    return 3;
}

QVariant CalculateSize_TableModel::data(const QModelIndex &index, int role) const{

    switch (role) {
        case Qt::DisplayRole:
            if(index.row() == 0 && index.column() == 0){
                return "fdsfd";
            }
            return "dad";
        break;
    }
    return QVariant();
}


QVariant CalculateSize_TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("first");
        case 1:
            return QString("second");
        case 2:
            return QString("third");
        }
    }
    return QVariant();
}
