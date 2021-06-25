#ifndef CALCULATESIZE_TABLEMODEL_H
#define CALCULATESIZE_TABLEMODEL_H

#include <QAbstractTableModel>
#include "Context_CalculateSize.h"
#include "ISubject.h"

class CalculateSize_TableModel : public QAbstractTableModel, public ISubject{

    Q_OBJECT

    public:

        CalculateSize_TableModel(QObject *parent);
        ~CalculateSize_TableModel();

        void Attach(IObserver *observer) override;
        void Detach(IObserver *observer) override;
        void Notify() override;

        int rowCount(const QModelIndex &index = QModelIndex())const override;
        int columnCount(const QModelIndex &index = QModelIndex())const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        void append(QString path);
        void changeStrat(Context_CalculateSize::Strategies strat, QString path);
        Context_CalculateSize* getContext(){return context;}
        QMap<QString, QList<float>> getMap(){return map;}

    private:

        QMap<QString, QList<float>> map;
        Context_CalculateSize *context;
        std::list<IObserver *> list_observer_;

};

#endif // CALCULATESIZE_TABLEMODEL_H
