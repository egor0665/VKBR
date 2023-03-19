#include "tabcomparisonmodel.h"
#include <QDebug>

TabComparisonModel::TabComparisonModel()
{

}

TabComparisonModel::TabComparisonModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

QVector<QPair<QString,QStringList>> TabComparisonModel::formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2)
{
    QVector<QPair<QString,QStringList>> compareVector;
    QVector<QPair<QString,QStringList>> singleValuesVector;
    for (int i=0; i<unitValues_1.length();i++)
    {
        QString compVal = unitValues_1[i].first;
        bool found = false;
        for (int j=0;j<unitValues_2.length();j++)
        {
            if (unitValues_2[j].first==compVal){
                compareVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second,unitValues_2[j].second}));
                found=true;
                break;
            }
        }
        if (!found) {
            singleValuesVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second, ""}));
        }
    }

    for (int i=0; i<unitValues_2.length();i++)
    {
        QString compVal = unitValues_2[i].first;
        bool found = false;
        for (int j=0;j<unitValues_1.length();j++)
        {
            if (unitValues_1[j].first==compVal){
                found=true;
                break;
            }
        }
        if (!found) {
            singleValuesVector.append(QPair<QString,QStringList>(compVal, { "", unitValues_2[i].second}));
        }
    }
    compareVector.append(singleValuesVector);
    return compareVector;
}

qreal TabComparisonModel::getNumberFromString(QString line, int param)
{
    //param
    // 0 - first
    // 1 - min
    // 2 - max
    // 3 - last
    qreal first,min,max,last,cur,divider;
    int i=0;
    bool firstNum = true;
    while (i<= line.length())
    {
        cur = 0;
        divider = 1;
        bool gotDivider=false;
        bool gotNum = false;
        while (line[i].isDigit() || line[i]=="." || line[i]==",")
        {
            if (gotDivider)
                divider /= 10;
            if (line[i].isDigit())
                cur=cur*10+line[i].digitValue();
            else
                gotDivider = true;
            i++;
            gotNum = true;
        }
        if (gotNum)
        {
            cur *= divider;
            if (firstNum) {
                min = cur;
                max = cur;
                first = cur;
                firstNum = false;
            }
            if (cur<min) min = cur;
            if (cur>max) max = cur;
            last = cur;
            qDebug() << cur << last << first << min << max;
        }
        i++;
    }
    if (firstNum)
    {
        first = 0;
        min = 0;
        max = 0;
        last = 0;
        cur = 0;
    }
    switch (param) {
    case 0:
        return first;
    case 1:
        return min;
    case 2:
        return max;
    case 3:
        return last;
    default:
        return first;
    }
}
