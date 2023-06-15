#ifndef DIAGRAMWIDGETS_H
#define DIAGRAMWIDGETS_H

#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QMap>
#include <QList>
#include <QString>
#include "IObserver.h"
#include "CalculateSize_TableModel.h"

using namespace QtCharts;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class diagramwidgets;

class AbstractCreation
{

public:
    AbstractCreation(diagramwidgets *d_, QChart *qchart_, QChartView *qcharview_,
                     QMap<QString, QList<float>> map_)
        :

          qchart(qchart_),
          qcharview(qcharview_),
          map(map_),
          d(d_){};

    virtual ~AbstractCreation() { }

    float count = 1;
    QList<float> val;
    QString name;
    qreal yValue = 0;
    QChart *qchart;
    QChartView *qcharview;
    QMap<QString, QList<float>> map;
    diagramwidgets *d;

    void executeAll()
    {

        this->removePlusTitle_Hook("");
        qchart = this->MainAlgorithm();
        this->chartViewUpdate();
        this->setCurrentDiagram(d);
    }

    virtual void removePlusTitle_Hook(QString title)
    {
        qchart->removeAllSeries();
        qchart->setTitle(title);
    }

    virtual QChart *MainAlgorithm() = 0;

    virtual void chartViewUpdate() { qcharview->update(); }

    virtual void setCurrentDiagram(diagramwidgets *d) = 0;
};

class Bar : public AbstractCreation
{

public:
    Bar(diagramwidgets *d_, QChart *qchart_, QChartView *qcharview_,
        QMap<QString, QList<float>> map_)
        : AbstractCreation(d_, qchart_, qcharview_, map_)
    {
    }

    virtual QChart *MainAlgorithm() override
    {
        QStringList categories;
        QStackedBarSeries *series = new QStackedBarSeries(qchart);

        QMap<QString, QList<float>>::const_iterator i = map.begin();
        i++;
        if (i != map.end() + 1) {
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
            // series->clear();
            series->append(set);
        }

        qchart->addSeries(series);

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        qchart->createDefaultAxes();
        qchart->setAxisX(axis, series);

        return qchart;
    }

    void setCurrentDiagram(diagramwidgets *d) override;
};

class Pie : public AbstractCreation
{

public:
    Pie(diagramwidgets *d_, QChart *qchart_, QChartView *qcharview_,
        QMap<QString, QList<float>> map_)
        : AbstractCreation(d_, qchart_, qcharview_, map_)
    {
    }

    virtual QChart *MainAlgorithm() override
    {
        QMap<QString, QList<float>>::const_iterator i = map.begin();
        i++;
        if (i != map.end() + 1) {
            QPieSeries *series = new QPieSeries(qchart);

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
            qreal shiftPie = 0.98;
            qreal hPos = (pieSize / shiftPie) + (0.1 / (qreal)2);
            series->setPieSize(pieSize);
            series->setHorizontalPosition(hPos);
            series->setVerticalPosition(0.5);
            qchart->addSeries(series);
        }
        return qchart;
    }

    void setCurrentDiagram(diagramwidgets *d) override;
};

class diagramwidgets : public IObserver
{

public:
    enum CurrentDiagram { BarChart = 1, PieChart };

    diagramwidgets(CalculateSize_TableModel &subject);
    ~diagramwidgets();

    QChart *createBarChart();
    QChart *createPieChart();
    QChart *executeCurrentDiagram();
    DataTable generateData(QMap<QString, QList<float>> map);
    QChart *getQChartView();

    int m_listCount;
    int m_valueMax;
    int m_valueCount;

    QList<QChartView *> m_charts;
    QChartView *chartView;
    QChart *qChart;
    DataTable m_dataTable;
    Data m_data;
    DataList m_datalist;

    virtual void Update(QMap<QString, QList<float>> map);

private:
    CalculateSize_TableModel &subject_;
    CurrentDiagram currentDiagram;
    QMap<QString, QList<float>> map;
    static int static_number_;
    int number_;

    friend void Bar::setCurrentDiagram(diagramwidgets *d);
    friend void Pie::setCurrentDiagram(diagramwidgets *d);
};

#endif // DIAGRAMWIDGETS_H
