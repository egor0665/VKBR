#ifndef UNITCOMPARATOR_H
#define UNITCOMPARATOR_H

#include <CompareValue.h>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/qpolarchart.h>
#include <QtCharts/QtCharts>



class UnitComparator
{
public:
    UnitComparator();
    void addValuesToComparison(QString parameter,  QVector <qreal> _values);
    void removeValuesFromComparison(QString parameter);
    void clearValues();
    const QVector<CompareValue> &compareValues() const;
    QVector <QLineSeries*> CreateChart(int unitNum=2);
    void addUnitName(QString name);
    QVector<CompareValue> getValues();


    const QStringList &unitNames() const;

    QPair<qreal,qreal> getMinMax();
    bool isEmpty();
private:
    QVector<CompareValue> _compareValues;
    QStringList _unitNames;
};



#endif // UNITCOMPARATOR_H
