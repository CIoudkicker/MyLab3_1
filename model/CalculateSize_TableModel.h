#ifndef CALCULATESIZE_TABLEMODEL_H
#define CALCULATESIZE_TABLEMODEL_H

#include "Context_CalculateSize.h"

#include "ModelUpdateTemplate.h"

class CalculateSize_TableModel : public ModelUpdateTemplate
{

    Q_OBJECT

public:
    CalculateSize_TableModel(QObject *parent);
    ~CalculateSize_TableModel();

    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    void RequiredOperations1(QString path);
    void RequiredOperations1(ICalculateSize *strat, QString path);

    void append(QString path);
    void changeStrat(ICalculateSize *strat, QString path);
    Context_CalculateSize *getContext() { return context; }
};

#endif // CALCULATESIZE_TABLEMODEL_H
