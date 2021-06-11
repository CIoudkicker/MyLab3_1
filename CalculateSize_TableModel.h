#ifndef CALCULATESIZE_TABLEMODEL_H
#define CALCULATESIZE_TABLEMODEL_H

#include <QAbstractTableModel>

class CalculateSize_TableModel : public QAbstractTableModel{

    Q_OBJECT

    public:

        CalculateSize_TableModel(QObject *parent);

        int rowCount(const QModelIndex &index = QModelIndex())const override;
        int columnCount(const QModelIndex &index = QModelIndex())const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    private:

        QMap<QString, QList<float>> map;
};

#endif // CALCULATESIZE_TABLEMODEL_H
