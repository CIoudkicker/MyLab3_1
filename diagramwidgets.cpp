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
    qChart->removeAllSeries();

    qChart->setTitle("Bar chart");

    QStringList categories;
    QStackedBarSeries *series = new QStackedBarSeries(qChart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (int j = 0; j < m_dataTable[i].size()-1; j++) {
            *set << m_dataTable[i][j].first.y();
            categories << categories << QString(m_dataTable[i][j].second);
        }
        *set << m_dataTable[i][m_dataTable[i].size()-1].first.y();
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
    qChart->removeAllSeries();
    qChart->setTitle("Pie chart");

    qreal pieSize = 0.5 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(qChart);
        for (int j = 0; j < m_dataTable[i].size()-1; j++) {
            QPieSlice *slice = series->append(m_dataTable[i][j].second, m_dataTable[i][j].first.y());
            slice->setLabelVisible();
            slice->setExploded();
        }
        qreal hPos = (pieSize / 0.98) + (i / (qreal) m_dataTable.count());
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



