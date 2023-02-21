#include "unitcomparator.h"

#include <CompareValue.h>

UnitComparator::UnitComparator()
{

}

void UnitComparator::addValuesToComparison(QString parameter, QVector<qreal> _values)
{
    _compareValues.append(CompareValue(parameter, _values));
}

void UnitComparator::removeValuesFromComparison(QString parameter)
{
    int i=0;
    while (_compareValues[i]._parameter!=parameter){
        i++;
    }
    _compareValues.remove(i);
}

void UnitComparator::clearValues()
{
    _compareValues.clear();
    _unitNames.clear();
}

const QVector<CompareValue> &UnitComparator::compareValues() const
{
    return _compareValues;
}

QVector <QLineSeries*> UnitComparator::CreateChart(int unitNum)
{
    QVector <QLineSeries*> seriesSummary;

    int compNum = _compareValues.length();
    for (int i=0;i<unitNum;i++){
        QLineSeries *series = new QLineSeries();
        series->setName(_unitNames[i]);
        for (int j=0;j<compNum;j++){
            series->append(j, _compareValues[j]._values[i]);
            qDebug() << j<< _compareValues[j]._values[i];
        }
        series->append(compNum+1,_compareValues[0]._values[i]);
        qDebug() << 0<< _compareValues[0]._values[i];
        seriesSummary.append(series);
    }

    return seriesSummary;
}

bool UnitComparator::isEmpty()
{
    return _compareValues.length() < 1;
}

QPair<qreal,qreal> UnitComparator::getMinMax()
{
    int min = _compareValues[0]._values[0];
    int max = _compareValues[0]._values[0];
    for (int i=0;i<_compareValues[0]._values.length();i++){
        for(int j=0;j<_compareValues.length();j++){
            if (_compareValues[j]._values[i]<min) min = _compareValues[j]._values[i];
            if (_compareValues[j]._values[i]>max) max = _compareValues[j]._values[i];
        }
    }
    return QPair<qreal,qreal>(min,max);
}

void UnitComparator::addUnitName(QString name)
{
    _unitNames.append(name);
}

QVector<CompareValue> UnitComparator::getValues()
{
    return _compareValues;
}

const QStringList &UnitComparator::unitNames() const
{
    return _unitNames;
}
