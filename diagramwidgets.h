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
#include <QMap>
#include <QList>
#include <QString>
#include "IObserver.h"
#include "CalculateSize_TableModel.h"
#include "AbstractCreation.h"
#include "PieChart.h"
#include "BarChart.h"

using namespace QtCharts;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class diagramwidgets;

class diagramwidgets : public IObserver
{

public:
    enum CurrentDiagram { BarChart = 1, PieChart };

    diagramwidgets(CalculateSize_TableModel &subject);
    ~diagramwidgets();

    QChart *executeCurrentDiagram();
    void changeChart(AbstractCreatio *newChartn);
    DataTable generateData(DataForTable map);
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
    AbstractCreation createChart;

    virtual void Update(DataForTable map);

private:
    CalculateSize_TableModel &subject_;
    DataForTable map;
    static int static_number_;
    int number_;
};

#endif // DIAGRAMWIDGETS_H
