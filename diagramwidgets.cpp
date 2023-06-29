#include "diagramwidgets.h"

diagramwidgets::diagramwidgets(CalculateSize_TableModel &subject)
    : m_dataTable(DataTable()), subject_(subject)
{
    this->subject_.Attach(this);
    this->qChart = new QChart();

    this->chartView = new QChartView();

    this->chartView->setChart(qChart);
}

diagramwidgets::~diagramwidgets()
{
    delete chartView;
}

void diagramwidgets::Update(DataForTable map)
{
    generateData(map);
    executeCurrentDiagram();
}

void diagramwidgets::changeChart(AbstractCreation *newChart)
{
    if (actualChart != nullptr) {
        delete actualChart;
    }
    actualChart = actualChart;
}

QChart *diagramwidgets::executeCurrentDiagram()
{
    qChart = actualChart->executeAll();
    return qChart;
}

DataTable diagramwidgets::generateData(DataForTable map)
{
    DataTable dataTable;
    float count = -1;
    QList<float> val;
    QString name;

    DataForTable::const_iterator i = map.begin();
    i++;
    if (i != map.end() + 1) {
        qreal yValue(0);
        DataList dataList;
        while (i != map.end()) {
            count += 1;
            val = i.value();
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

    this->map = map;
    m_dataTable = dataTable;
    return dataTable;
}
