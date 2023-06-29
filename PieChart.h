#ifndef PIECHART_H
#define PIECHART_H

#include "AbstractCreation.h"

class PieChart : public AbstractCreation
{

public:
    PieChart(diagramwidgets *d_, QChart *qchart_, QChartView *qcharview_, DataForTable map_)
        : AbstractCreation(d_, qchart_, qcharview_, map_)
    {
    }

    virtual QChart *MainAlgorithm() override
    {
        DataForTable::const_iterator i = map.begin();
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
};

#endif // PIECHART_H
