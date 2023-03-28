#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <CompareValue.h>
#include <QtCharts>
#include <qDebug>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/qpolarchart.h>
#include <QtCharts/QtCharts>

class ChartManager
{
public:
    ChartManager();
    QVector <QLineSeries*> CreateChart(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames);
};

#endif // CHARTMANAGER_H
