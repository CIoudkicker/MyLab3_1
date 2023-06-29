#ifndef BARCHART_H
#define BARCHART_H

#include "AbstractCreation.h"

class BarChart : public AbstractCreation
{

public:
    BarChart(diagramwidgets *d_, QChart *qchart_, QChartView *qcharview_, DataForTable map_)
        : AbstractCreation(d_, qchart_, qcharview_, map_)
    {
    }

    virtual QChart *MainAlgorithm() override
    {
        QStringList categories;
        QStackedBarSeries *series = new QStackedBarSeries(qchart);

        DataForTable::const_iterator i = map.begin();
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

    void setCurrentDiagram(diagramwidgets *d)
    {
        d->currentDiagram = diagramwidgets::CurrentDiagram::BarChart;
    }
};

#endif // BARCHART_H
