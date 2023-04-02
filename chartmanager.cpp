#include "chartmanager.h"

#include <CompareValue.h>

ChartManager::ChartManager()
{

}

QVector <QLineSeries*> ChartManager::CreateChartLineSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
{
    QVector <QLineSeries*> seriesSummary;

    int compNum = compareValues.length();
    for (int i=0;i<unitNum;i++){
        QLineSeries *series = new QLineSeries();
        series->setName(unitNames[i]);
        for (int j=0;j<compNum;j++){
            series->append(j, compareValues[j]._values[i]);
            qDebug() << j<< compareValues[j]._values[i];
        }
        //series->append(compNum,compareValues[0]._values[i]);
        qDebug() << 0 << compareValues[0]._values[i];
        seriesSummary.append(series);
    }

    return seriesSummary;
}

QBarSeries* ChartManager::CreateChartBarSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
{
    QBarSeries* seriesSummary = new QBarSeries;
    int compNum = compareValues.length();
    for (int i=0;i<unitNum;i++){
        QBarSet *set = new QBarSet(unitNames[i]);
        for (int j=0;j<compNum;j++){
            *set <<compareValues[j]._values[i];
            qDebug() << compareValues[j]._values[i];
        }
        seriesSummary->append(set);
        qDebug() << 0 << compareValues[0]._values[i];
    }

    return seriesSummary;
}



