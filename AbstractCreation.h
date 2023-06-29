#ifndef ABSTRACTCREATION_H
#define ABSTRACTCREATION_H

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

#include "diagramwidgets.h"

using namespace QtCharts;

class AbstractCreation
{
public:
    AbstractCreation(QChart *qchart_, QChartView *qcharview_, DataForTable map_)
        : qchart(qchart_), qcharview(qcharview_), map(map_), d(d_)
    {
    }

    virtual ~AbstractCreation() { }

    float count = 1;
    QList<float> val;
    QString name;
    qreal yValue = 0;
    QChart *qchart;
    QChartView *qcharview;
    DataForTable map;

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
#endif // ABSTRACTCREATION_H
