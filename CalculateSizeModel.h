#ifndef CALCULATESIZEMODEL_H
#define CALCULATESIZEMODEL_H

#include <iostream>
#include <QAbstractListModel>
#include "Folder_CalculateSize.h"
#include "Context.h"
#include <QList>
#include <QMap>
#include <QString>

using namespace std;

class CalculateSizeModel : public QAbstractListModel
{
    public:

        CalculateSizeModel(QObject *parent);
        ~CalculateSizeModel();

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

        void append(QString path);

        //void appendRow(const)


        QMap<QString, QList<float>> map;
};

#endif // CALCULATESIZEMODEL_H
