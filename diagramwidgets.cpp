#include "diagramwidgets.h"

diagramwidgets::diagramwidgets(CalculateSize_TableModel &subject):
    m_dataTable(DataTable()), subject_(subject)
{
    this->subject_.Attach(this);
    this->qChart = new QChart();;

    this->chartView = new QChartView();

    this->chartView->setChart(qChart);

}

diagramwidgets::~diagramwidgets(){
    delete chartView;
}

void diagramwidgets::Update(QMap<QString, QList<float>> map){
    generateData(map);
    executeCurrentDiagram();
}

QChart *diagramwidgets::createBarChart()
{

    float count = -1;
    QList<float> val;
    QString name;
    qreal yValue(0);

    AbstractCreation *bar = new Bar(this,qChart,chartView,map);

    bar->executeAll();

    return qChart;
}


QChart* diagramwidgets::createPieChart()
{
    float count = -1;
    QList<float> val;
    QString name;
    qreal yValue(0);

    AbstractCreation *pie = new Pie(this,qChart,chartView,map);

    pie->executeAll();

    return qChart;
}
QChart* diagramwidgets::executeCurrentDiagram(){
    switch (currentDiagram) {

        case BarChart:
            createBarChart();
            break;

        case PieChart:
            createPieChart();
            break;
    }
}

DataTable diagramwidgets::generateData(QMap<QString, QList<float>> map)
{
    DataTable dataTable;
    float count = -1;
    QList<float> val;
    QString name;


    QMap<QString, QList<float>>::const_iterator i = map.begin();
    i++;
    if(i != map.end()+1){
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

void Bar::setCurrentDiagram(diagramwidgets *d){
     d->currentDiagram = diagramwidgets::CurrentDiagram::BarChart;
}

void Pie::setCurrentDiagram(diagramwidgets *d){
     d->currentDiagram = diagramwidgets::CurrentDiagram::PieChart;
}

