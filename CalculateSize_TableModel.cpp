#include "CalculateSize_TableModel.h"

CalculateSize_TableModel::CalculateSize_TableModel(QObject *parent):
    QAbstractTableModel(parent)
{
    map = QMap<QString, QList<float>>();
}


int CalculateSize_TableModel::rowCount(const QModelIndex &)const {
    return map.count();
}


int CalculateSize_TableModel::columnCount(const QModelIndex &)const {
    return 3;
}

QVariant CalculateSize_TableModel::data(const QModelIndex &index, int role) const{

    switch (role) {
        case Qt::DisplayRole:
            QMap<QString, QList<float>>::const_iterator i = map.begin();
            i += index.row();
            if(map.empty()){
                return QVariant();;
            }

            if(i.value().count()> 1){
                QString size = QString::number(i.value()[0],'g', 20);
                QString procent = QString::number(i.value()[1]);
                if(index.column() == 0) return i.key();
                if(index.column() == 1) return size;
                if(index.column() == 2) return procent;
                return i.key() + " size " + size + " procent " + procent;
            }else if (i.value().count() == 1){
                QString size = QString::number(i.value()[0],'g', 20);
                if(index.column() == 0) return "Total Size";
                if(index.column() == 1) return size;
                if(index.column() == 2) return "";
            }
        break;
    }
    return QVariant();
}


QVariant CalculateSize_TableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void CalculateSize_TableModel::append(QString path){
    beginInsertRows(QModelIndex(), map.count(), map.count());
    Context *conext = new Context;
    QMap<QString, QList<float>> folder_size = conext->dirSize(new Folder_CalculateSize(path));
    map = folder_size;
    endInsertRows();
}
