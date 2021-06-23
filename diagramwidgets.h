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


using namespace QtCharts;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class diagramwidgets{

    public:

        diagramwidgets();

        QChart *createBarChart(int valueCount) const;
        DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;

        int m_listCount;
        int m_valueMax;
        int m_valueCount;

        QList<QChartView *> m_charts;
        DataTable m_dataTable;
        QComboBox *m_themeComboBox;
        QCheckBox *m_antialiasCheckBox;
        QComboBox *m_animatedComboBox;
        QComboBox *m_legendComboBox;


};

#endif // DIAGRAMWIDGETS_H