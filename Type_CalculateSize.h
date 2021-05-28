#ifndef TYPE_CALCULATESIZE_H
#define TYPE_CALCULATESIZE_H
#include "ICalculateSize.h"

class Type_CalculateSize : public ICalculateSize{

    public:

        Type_CalculateSize(QString path1): ICalculateSize(path1){}
        ~Type_CalculateSize(){}

        virtual QMap<QString, QList<float>> dirSize();
        virtual QMap<QString, QList<float>> dirSize(const QString &path, int level, QMap<QString, QList<float>> map1);
        virtual QMap<QString, QList<float>> dirSize(const QString &path);
        QString getType(QString s);

        int size = 0;
};

#endif // TYPE_CALCULATESIZE_H
