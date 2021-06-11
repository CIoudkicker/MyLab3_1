#include "CalculateSizeModel.h"

CalculateSizeModel::CalculateSizeModel(QObject *parent):
    QAbstractListModel(parent)
{
    map = QMap<QString, QList<float>>();
}


CalculateSizeModel::~CalculateSizeModel(){

}


int CalculateSizeModel::rowCount(const QModelIndex &)const {
    return CalculateSizeModel::map.count();
}

QVariant CalculateSizeModel::data(const QModelIndex &index, int role) const {
    switch (role) {
        case Qt::DisplayRole:
            QMap<QString, QList<float>>::const_iterator i = map.begin();
            i += index.row();
            QString size = QString::number(i.value()[0],'g', 20);
            if(i.value().count()> 1){
                QString procent = QString::number(i.value()[1],'g', 20);
                return i.key() + " size " + size + " procent " + procent;
            }else{
                return i.key() + " size " + size;
            }

        break;
    }
    return QVariant();
}

bool CalculateSizeModel::removeRows(int row, int count, const QModelIndex &/*parent*/)
{
    if (row > -1 && (row + count - 1) < map.count()) {
        beginRemoveRows(QModelIndex(), row, row + count - 1);
        int  a = 1;
        endRemoveRows();
        return true;
    }

    return false;
}

void CalculateSizeModel::append(QString path){
    beginInsertRows(QModelIndex(), map.count(), map.count());
    Context *conext = new Context;
    QMap<QString, QList<float>> folder_size = conext->dirSize(new Folder_CalculateSize(path));
    map = folder_size;

    endInsertRows();
}
