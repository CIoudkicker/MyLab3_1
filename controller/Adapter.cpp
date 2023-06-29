#include "Adapter.h"


Adapter::Adapter(CalculateSize_TableModel *adaptee) :
    adaptee_(adaptee),
    diagramwidgets(*adaptee)
{

}


DataTable Adapter::generateData(QMap<QString, QList<float>> map_)
{
    QMap<QString, QList<float>> map = adaptee_->getMap();
    DataTable dataTable;
    float count = -1;
    QMap<QString, QList<float>>::const_iterator i = map.begin();
    i++;
    if(i != map.end()+1){
        qreal yValue(0);
        DataList dataList;
        while (i != map.end()) {
            count += 1;
            QList<float> val = i.value();
            yValue = val[1];
            QPointF value_1(1, yValue);
            QString label = QString(i.key());
            dataList << Data(value_1, label);
            i++;
        }
        QString label = QString(i.key());
        QPointF value_1(1, 100);
        dataList << Data(value_1, label);
        dataTable << dataList;
    }

    m_dataTable = dataTable;
    return dataTable;
}
