#ifndef ADAPTER_H
#define ADAPTER_H
#include "CalculateSize_TableModel.h"
#include "diagramwidgets.h"

class Adapter : diagramwidgets
{
    public:

        Adapter(CalculateSize_TableModel *adaptee);
        DataTable generateData(QMap<QString, QList<float>> map_);

    private:
        CalculateSize_TableModel *adaptee_;
};

#endif // ADAPTER_H
