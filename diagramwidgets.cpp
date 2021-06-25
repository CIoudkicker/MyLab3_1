#include "diagramwidgets.h"

diagramwidgets::diagramwidgets(CalculateSize_TableModel &subject):
    m_dataTable(DataTable()), subject_(subject)
{
    this->subject_.Attach(this);
    //std::cout << "Hi, I'm the Observer \"" << ++diagramwidgets::static_number_ << "\".\n";
    //this->number_ = diagramwidgets::static_number_;

    QChartView *chartView;
    chartView = new QChartView();
    m_charts << chartView;
    this->chartView = chartView;

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

    this->chartView->setChart(chart);
    chartView->update();
    qChart = chart;

    currentDiagram = CurrentDiagram::BarChart;
    return chart;
}

QChart* diagramwidgets::createPieChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    qreal pieSize = 0.5 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        for (int j = 0; j < m_dataTable[i].size()-1; j++) {
            QPieSlice *slice = series->append(m_dataTable[i][j].second, m_dataTable[i][j].first.y());
            slice->setLabelVisible();
            slice->setExploded();
        }
        qreal hPos = (pieSize / 0.98) + (i / (qreal) m_dataTable.count());
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);
        chart->addSeries(series);
    }
    qChart = chart;
    this->chartView->setChart(chart);
    chartView->update();

    currentDiagram = CurrentDiagram::PieChart;

    return chart;
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

    this->map = map;
    m_dataTable = dataTable;
    return dataTable;
}



