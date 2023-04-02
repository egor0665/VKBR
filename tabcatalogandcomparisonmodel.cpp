#include "tabcatalogandcomparisonmodel.h"
#include <QDebug>
#include <QVector>

TabCatalogAndComparisonModel::TabCatalogAndComparisonModel()
{

}
TabCatalogAndComparisonModel::TabCatalogAndComparisonModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::splitValues(QString values)
{
    qDebug()<<"splitvalues" + values;
    QVector<QPair<QString,QString>> resultValues;
    QStringList stringVals = values.split("\n");
    for (int j=0;j<stringVals.length();j++){
        QStringList pair = stringVals[j].split("==");
        resultValues.append(QPair<QString,QString>(pair[0], pair[1]));
    }
    return resultValues;
}

QString TabCatalogAndComparisonModel::getUnitImageFromId(int unitId)
{
    return mainModel->db.getUnitImageFromId(unitId);
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::getUnitData(int unitId)
{
    QVector<QPair<QString,QString>> result = vectorUnitData(unitId);
    QString unitClass = mainModel->db.getUnitClassById(unitId);
    if (unitClass == "РН")
        result.append(vectorBoosterRocketData(unitId));
    else if (unitClass == "РБ")
        result.append(vectorUpperBlockData(unitId));

    qDebug() << result;
    return result;
}

int TabCatalogAndComparisonModel::getUnitIdByName(QString unitName)
{
    return  mainModel->db.getUnitIdByName(unitName);
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::vectorUnitData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBUnit selectedUnit = mainModel->db.getUnitInfoFromId(unitId);

    QStringList values = selectedUnit.getValues();
    for (int i=0;i<selectedUnit.UNIT_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUnit.UNIT_VALUES[i] == "Разработчик" || selectedUnit.UNIT_VALUES[i] == "Разработчик 2" || selectedUnit.UNIT_VALUES[i] == "Производитель" || selectedUnit.UNIT_VALUES[i] == "Заказчик")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], mainModel->db.getOrganizationInfoFromId(values[i].toInt()).name()));
            else if (selectedUnit.UNIT_VALUES[i] == "Космодром первого запуска")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], mainModel->db.getSpaceportInfoFromId(values[i].toInt()).name()));
            else
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::vectorBoosterRocketData(int boosterRocketId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBBooster_rocket selectedBooster_rocket = mainModel->db.getBooster_rocketInfoFromId(boosterRocketId);
    QStringList values = selectedBooster_rocket.getValues();
    for (int i=0;i<selectedBooster_rocket.BOOSTER_ROCKET_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="phys_info" || selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="econ_info")
                vectoredData.append(splitValues(values[i]));
            else
                vectoredData.append(QPair<QString,QString>(selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector <QPair<QString,QString>> TabCatalogAndComparisonModel::vectorUpperBlockData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBUpper_block selectedUpper_block =  mainModel->db.getUpper_blockInfoFromId(unitId);
    QStringList values = selectedUpper_block.getValues();
    for (int i=0;i<selectedUpper_block.UPPER_BLOCK_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUpper_block.UPPER_BLOCK_VALUES[i]=="phys_info" || selectedUpper_block.UPPER_BLOCK_VALUES[i]=="econ_info")
                vectoredData.append(splitValues(values[i]));
            else
                vectoredData.append(QPair<QString,QString>(selectedUpper_block.UPPER_BLOCK_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

void TabCatalogAndComparisonModel::createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot)
{
    navigatiorMenuRoot->setText(0, "Каталог");
    QVector <QPair<QString,QString>> units = mainModel->db.getUnitClassesAndNames();
    qDebug() << units;
    QString lastclass = "";
    QVector <QString> nameArray;

    for (int i=0;i < units.size();i++){
        QString _class = units[i].first;
        QString _name = units[i].second;

        if (lastclass!=_class){
            if (!nameArray.empty()){
                addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
            }
            nameArray.clear();
            lastclass = _class;
        }
        nameArray.append(_name);

    }
    addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
    return;
}

void TabCatalogAndComparisonModel::addTreeChild(QTreeWidgetItem *parent,
                              QString name, QVector <QString> child_array)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    for (int i=0; i<child_array.size();i++){
        addTreeChild2(treeItem, child_array[i]);
    }

}
void TabCatalogAndComparisonModel::addTreeChild2(QTreeWidgetItem *parent,
                               QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
}

QString TabCatalogAndComparisonModel::classSelect(QString _class)
{
    qDebug() << _class;
    QString resultClass;
    if (_class == "РН")
        resultClass = "Ракеты-носители";
    else if (_class == "РБ")
        resultClass = "Разгонные блоки";
    else if (_class == "ПГК")
        resultClass = "Пилотируемые и грузовые космические корабли/аппара";
    else if (_class == "КАС")
        resultClass = "Космические аппараты связи, вещания и ретрансляции, поиска и спасения";
    else
        resultClass = _class;
    qDebug() << _class << resultClass << endl;
    return resultClass;
}

QVector<QPair<QString,QStringList>> TabCatalogAndComparisonModel::formCompareTable(QVector<QVector<QPair<QString,QString>>> values)
{
    QMap<QString,bool> usedValues;
    QVector<QPair<QString,QStringList>> compareVector;
    for (int i=0;i<values.length();i++)
    {
        for (int j=0;j<values[i].length();j++)
        {
            usedValues[values[i][j].first] = false;
        }
    }

    for (int i=0;i<values.length();i++)
    {
        for (int j=0;j<values[i].length();j++)
        {
            QStringList currentValues = {};
            if (!usedValues[values[i][j].first])
            {
                for (int k=0;k<values.length();k++)
                {
                    bool foundValuesInUnit = false;
                    for (int y=0;y<values[k].length();y++)
                    {
                        if (values[k][y].first == values[i][j].first)
                        {
                            foundValuesInUnit = true;
                            currentValues.append(values[k][y].second);
                        }
                    }
                    if (!foundValuesInUnit)
                        currentValues.append("");
                }
                usedValues[values[i][j].first] = true;
                compareVector.append(QPair<QString,QStringList>(values[i][j].first,currentValues));
            }
        }
    }

//    QVector<QPair<QString,QStringList>> singleValuesVector;
//    for (int i=0; i<unitValues_1.length();i++)
//    {
//        QString compVal = unitValues_1[i].first;
//        bool found = false;
//        for (int j=0;j<unitValues_2.length();j++)
//        {
//            if (unitValues_2[j].first==compVal){
//                compareVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second,unitValues_2[j].second}));
//                found=true;
//                break;
//            }
//        }
//        if (!found) {
//            singleValuesVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second, ""}));
//        }
//    }

//    for (int i=0; i<unitValues_2.length();i++)
//    {
//        QString compVal = unitValues_2[i].first;
//        bool found = false;
//        for (int j=0;j<unitValues_1.length();j++)
//        {
//            if (unitValues_1[j].first==compVal){
//                found=true;
//                break;
//            }
//        }
//        if (!found) {
//            singleValuesVector.append(QPair<QString,QStringList>(compVal, { "", unitValues_2[i].second}));
//        }
//    }
//    compareVector.append(singleValuesVector);
    return compareVector;
}

QVector <QLineSeries*> TabCatalogAndComparisonModel::createChartLineSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
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
        qDebug() << 0 << compareValues[0]._values[i];
        seriesSummary.append(series);
    }

    return seriesSummary;
}

QBarSeries* TabCatalogAndComparisonModel::createChartBarSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
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

qreal TabCatalogAndComparisonModel::getNumberFromString(QString line, int param)
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
