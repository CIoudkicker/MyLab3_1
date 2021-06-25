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


class diagramwidgets : public IObserver{

    public:

        enum CurrentDiagram{
            BarChart = 1,
            PieChart
        };

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


        virtual void Update(QMap<QString, QList<float>> map);

    private:

        CalculateSize_TableModel &subject_;
        CurrentDiagram currentDiagram;
        QMap<QString, QList<float>> map;
        static int static_number_;
        int number_;

};

#endif // DIAGRAMWIDGETS_H
