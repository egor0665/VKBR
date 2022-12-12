#include "mainmodel.h"
#include <QVariant>
#include <QDebug>
#include <QGraphicsPixmapItem>

MainModel::MainModel()
{
    db = database();
    db.createConnection();
}

void MainModel::createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot)
{
    navigatiorMenuRoot->setText(0, "Каталог");
    QVector <QPair<QString,QString>> units = db.getUnitClassesAndNames();
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

void MainModel::addTreeChild(QTreeWidgetItem *parent,
                              QString name, QVector <QString> child_array)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    for (int i=0; i<child_array.size();i++){
        addTreeChild2(treeItem, child_array[i]);
    }

}
void MainModel::addTreeChild2(QTreeWidgetItem *parent,
                               QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
}

QString MainModel::classSelect(QString _class)
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

QVector<QPair<QString,QString>> MainModel::getUnitData(int unitId)
{
    QVector<QPair<QString,QString>> result = vectorUnitData(unitId);
    QString unitClass = db.getUnitClassById(unitId);
    if (unitClass == "РН")
        result.append(vectorBoosterRocketData(unitId));
    else if (unitClass == "РБ")
        result.append(vectorUpperBlockData(unitId));

    qDebug() << result;
    return result;
}
QVector<QPair<QString,QStringList>> getUnitEconData(int unitId)
{
    db.get
}

int MainModel::getUnitIdByName(QString unitName)
{
    return db.getUnitIdFromName(unitName);
}

QVector<QPair<QString,QString>> MainModel::vectorUnitData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    Unit selectedUnit = db.getUnitInfoFromId(unitId);

    QStringList values = selectedUnit.getValues();
    for (int i=0;i<selectedUnit.UNIT_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (i==6 || i==7 || i==10)
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getOrganizationInfoFromId(values[i].toInt()).name()));
            else if (i == 12)
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getSpaceportInfoFromId(values[i].toInt()).name()));
            else
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QPair<QString,QString>> MainModel::vectorBoosterRocketData(int boosterRocketId)
{
    QVector<QPair<QString,QString>> vectoredData;
    Booster_rocket selectedBooster_rocket = db.getBooster_rocketInfoFromId(boosterRocketId);
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

QVector <QPair<QString,QString>> MainModel::vectorUpperBlockData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    Upper_block selectedUpper_block = db.getUpper_blockInfoFromId(unitId);
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

QVector<QPair<QString,QString>> MainModel::splitValues(QString values)
{
    QVector<QPair<QString,QString>> resultValues;
    QStringList stringVals = values.split("\n");
    for (int j=0;j<stringVals.length();j++){
        QStringList pair = stringVals[j].split("==");
        resultValues.append(QPair<QString,QString>(pair[0], pair[1]));
    }
    return resultValues;
}

QVector<QPair<QString,QStringList>> MainModel::formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2)
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

QString MainModel::getUnitImageFromId(int unitId)
{
    return db.getUnitImageFromId(unitId);
}
