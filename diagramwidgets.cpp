#include "diagramwidgets.h"

diagramwidgets::diagramwidgets():
    m_dataTable(DataTable())
{
    QChartView *chartView;
    chartView = new QChartView(createBarChart(m_valueCount));
    m_charts << chartView;

}

QChart *diagramwidgets::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data &data : m_dataTable[i]){
            *set << data.first.y();
        }
        //series->clear();
        series->append(set);
    }
    chart->addSeries(series);
    QStringList categories;
    QMap<QString, QList<float>>::const_iterator i = map.begin();
    i++;
    if(i != map.end()+1){
        while (i != map.end()) {
            QList<float> val;
            val = i.value();
            categories << categories << QString(i.key());
            i++;
        }
    }

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    return chart;
}

QChart* diagramwidgets::createPieChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    qreal pieSize = 0.7 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        for (const Data &data : m_dataTable[i]) {
            QPieSlice *slice = series->append(data.second, /*data.first.y()*/ 43);
            slice->setLabelVisible();
            slice->setExploded();
            /*
            if (data == m_dataTable[i].first()) {
                slice->setLabelVisible();
                slice->setExploded();
            }*/
        }
        qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);

        chart->addSeries(series);
    }

    return chart;
}

DataTable diagramwidgets::generateData(QMap<QString, QList<float>> map)
{
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
            QString label = "Slice " + QString::number(0) + ":" + QString::number(count);
            dataList << Data(value_1, label);
            i++;
        }
        QString label = "Slice " + QString::number(0) + ":" + QString::number(count+1);
        QPointF value_1(1, 100);
        dataList << Data(value_1, label);
        dataTable << dataList;
    }

    this->map = map;
    m_dataTable = dataTable;
    return dataTable;
}



