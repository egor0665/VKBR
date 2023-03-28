#include "chartmanager.h"

#include <CompareValue.h>

ChartManager::ChartManager()
{

}

QVector <QLineSeries*> ChartManager::CreateChart(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
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

//void ChartManager::buildChart(qreal minVal, qreal maxVal, QVector<QPair<QString,<QVector<qreal>>> values )
//{
//    if (comparator.isEmpty()) return ;
//    //model.
//    QPair<qreal,qreal> minMax = comparator.getMinMax();
//    const qreal angularMin = 0;
//    const qreal angularMax = 10;

//    const qreal radialMin = minMax.first;
//    const qreal radialMax = minMax.second;

//    //qDebug()<<radialMin<<radialMax;
//    QPolarChart *chart = new QPolarChart();
//    QVector <QLineSeries*> seriesSummary = comparator.CreateChart();
//    for (int i=0;i<seriesSummary.length();i++){
//        qDebug() << seriesSummary[i];
//        chart->addSeries(seriesSummary[i]);
//    }

//    chart->setTitle("Сравнение аппаратов");

//    QValueAxis *angularAxis = new QValueAxis();
//    angularAxis->setTickCount(0);
//    angularAxis->setLabelFormat("%.1f");
//    angularAxis->setShadesVisible(true);
//    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
//    angularAxis->setMax(angularMax);
//    angularAxis->setMin(angularMin);
//    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

//    QValueAxis *radialAxis = new QValueAxis();
//    radialAxis->setTickCount(0);
//    radialAxis->setLabelFormat("%d");
//    radialAxis->setMax(angularMax);
//    radialAxis->setMin(angularMin);
//    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
//    //chartDialog *chartdialog = new chartDialog(this, chart);
//    //chartdialog->show();
//    ui->widget->setChart(chart);
//    qDebug()<<"";
//    qDebug()<<"MinMax"<<radialMin<<radialMax;
//}
