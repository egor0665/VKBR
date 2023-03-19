#include "DBspacecraft.h"
#include "mainmodel.h"
#include <QVariant>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <dbChangeValue.h>
#include <DBunit.h>
#include <DBProject.h>
#include <projectset.h>
#include <DBlaunch.h>

MainModel::MainModel()
{
    db = database();
    db.createConnection();
}

//QVector<QPair<QString,QString>> MainModel::getUnitData(int unitId)
//{
//    QVector<QPair<QString,QString>> result = vectorUnitData(unitId);
//    QString unitClass = db.getUnitClassById(unitId);
//    if (unitClass == "РН")
//        result.append(vectorBoosterRocketData(unitId));
//    else if (unitClass == "РБ")
//        result.append(vectorUpperBlockData(unitId));

//    qDebug() << result;
//    return result;
//}

//int MainModel::getUnitIdByName(QString unitName)
//{
//    return db.getUnitIdByName(unitName);
//}

//QVector<QPair<QString,QString>> MainModel::vectorUnitData(int unitId)
//{
//    QVector<QPair<QString,QString>> vectoredData;
//    DBUnit selectedUnit = db.getUnitInfoFromId(unitId);

//    QStringList values = selectedUnit.getValues();
//    for (int i=0;i<selectedUnit.UNIT_ROW_NUM; i++){
//        if (values[i]!="" && values[i]!="0"){
//            if (selectedUnit.UNIT_VALUES[i] == "Разработчик" || selectedUnit.UNIT_VALUES[i] == "Разработчик 2" || selectedUnit.UNIT_VALUES[i] == "Производитель" || selectedUnit.UNIT_VALUES[i] == "Заказчик")
//                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getOrganizationInfoFromId(values[i].toInt()).name()));
//            else if (selectedUnit.UNIT_VALUES[i] == "Космодром первого запуска")
//                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getSpaceportInfoFromId(values[i].toInt()).name()));
//            else
//                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], values[i]));
//        }
//    }
//    return vectoredData;
//}

//QVector<QPair<QString,QString>> MainModel::vectorBoosterRocketData(int boosterRocketId)
//{
//    QVector<QPair<QString,QString>> vectoredData;
//    DBBooster_rocket selectedBooster_rocket = db.getBooster_rocketInfoFromId(boosterRocketId);
//    QStringList values = selectedBooster_rocket.getValues();
//    for (int i=0;i<selectedBooster_rocket.BOOSTER_ROCKET_DEF_ROW_NUM; i++){
//        if (values[i]!="" && values[i]!="0"){
//            if (selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="phys_info" || selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="econ_info")
//                vectoredData.append(splitValues(values[i]));
//            else
//                vectoredData.append(QPair<QString,QString>(selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i], values[i]));
//        }
//    }
//    return vectoredData;
//}

//QVector <QPair<QString,QString>> MainModel::vectorUpperBlockData(int unitId)
//{
//    QVector<QPair<QString,QString>> vectoredData;
//    DBUpper_block selectedUpper_block = db.getUpper_blockInfoFromId(unitId);
//    QStringList values = selectedUpper_block.getValues();
//    for (int i=0;i<selectedUpper_block.UPPER_BLOCK_DEF_ROW_NUM; i++){
//        if (values[i]!="" && values[i]!="0"){
//            if (selectedUpper_block.UPPER_BLOCK_VALUES[i]=="phys_info" || selectedUpper_block.UPPER_BLOCK_VALUES[i]=="econ_info")
//                vectoredData.append(splitValues(values[i]));
//            else
//                vectoredData.append(QPair<QString,QString>(selectedUpper_block.UPPER_BLOCK_VALUES[i], values[i]));
//        }
//    }
//    return vectoredData;
//}

//QVector<QPair<QString,QString>> MainModel::splitValues(QString values)
//{
//    qDebug()<<"splitvalues" + values;
//    QVector<QPair<QString,QString>> resultValues;
//    QStringList stringVals = values.split("\n");
//    for (int j=0;j<stringVals.length();j++){
//        QStringList pair = stringVals[j].split("==");
//        resultValues.append(QPair<QString,QString>(pair[0], pair[1]));
//    }
//    return resultValues;
//}

QStringList MainModel::getNamesFromTableStringList(QString tableName)
{
     return QVectorToQStringList(getNamesFromTable(tableName));
}

QVector<QString> MainModel::getNamesFromTable(QString tableName)
{
    return db.getNamesFromTable(tableName);
}

QStringList MainModel::QVectorToQStringList(QVector<QString> vector)
{
    QStringList result = {};
    for (int i=0;i<vector.length();i++)
    {
        result.append(vector[i]);
    }
    return result;
}

//QString MainModel::getUnitImageFromId(int unitId)
//{
//    return db.getUnitImageFromId(unitId);
//}

void MainModel::updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload)
{
    int boosterRocketId = db.getUnitIdByName(boosterRocketName);
    int upperBlockId = db.getUnitIdByName(upperBlockName);
    int spaceportId = db.getSpaceportIdFromName(spaceportName);
    db.updateLaunchPricesByIds(boosterRocketId, upperBlockId, spaceportId,priceYear, prices, launchPrice, deliveryPrice, minPayload, maxPayload);
}
