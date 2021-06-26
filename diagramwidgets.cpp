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

    qChart->removeAllSeries();
    qChart->setTitle("Bar chart");

    QStringList categories;
    QStackedBarSeries *series = new QStackedBarSeries(qChart);




    QMap<QString, QList<float>>::const_iterator i = map.begin();
    i++;
    if(i != map.end()+1){
        QBarSet *set = new QBarSet("Bar set " + QString::number(11));
        while (i != map.end()) {
            count += 1;
            val = i.value();
            name = QString(i.key());
            yValue = val[1];
            *set << yValue;
            categories << categories << name;
            i++;
        }
        *set << (qreal)100;
        //series->clear();
        series->append(set);
    }


    qChart->addSeries(series);


    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    qChart->createDefaultAxes();
    qChart->setAxisX(axis, series);

    chartView->update();

    currentDiagram = CurrentDiagram::BarChart;
    return qChart;
}


QChart* diagramwidgets::createPieChart()
{
    float count = -1;
    QList<float> val;
    QString name;
    qreal yValue(0);

    qChart->removeAllSeries();
    qChart->setTitle("Pie chart");

    QMap<QString, QList<float>>::const_iterator i = map.begin();
    i++;
    if(i != map.end()+1){
        QPieSeries *series = new QPieSeries(qChart);

        while (i != map.end()) {
            count += 1;
            val = i.value();
            name = QString(i.key());
            yValue = val[1];
            QPieSlice *slice = series->append(name, yValue);
            slice->setLabelVisible();
            slice->setExploded();
            i++;
        }
        qreal pieSize = 0.5;
        qreal hPos = (pieSize / 0.98) + (0.1 / (qreal)2);
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);
        qChart->addSeries(series);
    }

    chartView->update();

    currentDiagram = CurrentDiagram::PieChart;

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



