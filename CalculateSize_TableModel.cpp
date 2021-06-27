#include "CalculateSize_TableModel.h"

CalculateSize_TableModel::CalculateSize_TableModel(QObject *parent):
    QAbstractTableModel(parent)
{
    map = QMap<QString, QList<float>>();
    context = new Context_CalculateSize;
}

void CalculateSize_TableModel::Attach(IObserver *observer){
  list_observer_.push_back(observer);
}

void CalculateSize_TableModel::Detach(IObserver *observer){
  list_observer_.remove(observer);
}

void CalculateSize_TableModel::Notify(){
  std::list<IObserver *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Update(map);
    ++iterator;
  }
}

CalculateSize_TableModel::~CalculateSize_TableModel(){
    delete context;
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
                if(index.column() == 2){
                    if(size != 0 && i.value()[1] == 0){
                        return "< 0.01";
                    }else{
                        return QString::number(i.value()[1]);
                    }
                }
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
    beginResetModel();

    context->changeStrat(context->getStrat(), path);
    map = context->getMap();
    Notify();
    endResetModel();
}

void CalculateSize_TableModel::changeStrat(Context_CalculateSize::Strategies strat, QString path){

    beginResetModel();

    context->changeStrat(strat, path);
    map = context->getMap();
    Notify();
    endResetModel();
}

