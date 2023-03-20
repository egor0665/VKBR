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

void MainModel::updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload)
{
    int boosterRocketId = db.getUnitIdByName(boosterRocketName);
    int upperBlockId = db.getUnitIdByName(upperBlockName);
    int spaceportId = db.getSpaceportIdFromName(spaceportName);
    db.updateLaunchPricesByIds(boosterRocketId, upperBlockId, spaceportId,priceYear, prices, launchPrice, deliveryPrice, minPayload, maxPayload);
}
