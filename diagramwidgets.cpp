#include "diagramwidgets.h"

diagramwidgets::diagramwidgets():
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(5),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))
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
        set->remove(2, 2);
        //series->clear();
        if(i != 100){
            series->append(set);
        }
    }
    chart->addSeries(series);
    QStringList categories;
    categories << "11" << "12" << "13";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);


    return chart;
}


DataTable diagramwidgets::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int count = 4;
    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            yValue = count;
            count += (4);
            QPointF value_1(100, yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value_1, label);
        }
        //count = count - (4*valueCount);
        dataTable << dataList;
    }

    return dataTable;
}

