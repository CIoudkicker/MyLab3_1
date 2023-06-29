#ifndef TYPE_CALCULATESIZE_H
#define TYPE_CALCULATESIZE_H
#include "ICalculateSize.h"

class Type_CalculateSize : public ICalculateSize
{

public:
    Type_CalculateSize(QString path1) : ICalculateSize(path1) { }
    ~Type_CalculateSize() { }

    virtual DataForTable dirSize() override;
    QString getType(QString s);

    int size = 0;

private:
    virtual DataForTable dirSize(const QString &path, int level, DataForTable map1);
    virtual DataForTable dirSize(const QString &path);
};

#endif // TYPE_CALCULATESIZE_H
