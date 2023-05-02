#include "tabnewextrasmodel.h"
#include <QDebug>

TabEditExtrasModel::TabEditExtrasModel()
{

}

//TabNewExtrasModel::TabNewExtrasModel(MainModel *_mainModel)
//{
//    mainModel = _mainModel;
//}

TabEditExtrasModel::TabEditExtrasModel(DataBase *db)
{
    this->db = db;
}

void TabEditExtrasModel::addOrganizationToDB(QString name)
{
    DBOrganization newOrganization = DBOrganization(-1, name);
    db->addOrganoizationToDB(newOrganization);
}

void TabEditExtrasModel::addSpaceportToDB(QString name)
{
    DBSpaceport newSpaceport = DBSpaceport(-1, name);
    db->addSpaceportToDB(newSpaceport);

    int spaceportId = db->getSpaceportIdFromName(name);
    QVector<int> boosterRocketIds = db->getIdsFromTable("booster_rocket");
    QVector<int> upperBlockIds = db->getIdsFromTable("upper_block");
    for (int i=0;i<boosterRocketIds.length();i++)
        for (int j=0;j<upperBlockIds.length();j++)
        {
            DBLaunch tmpLaunch = DBLaunch(-1, boosterRocketIds[i], upperBlockIds[j],spaceportId,2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0,false);
            db->addLaunchInformation(tmpLaunch);
        }
}

QStringList TabEditExtrasModel::getUnitNamesByTypeStringList(QString type)
{
    return QVectorToQStringList(db->getUnitNamesByType(type));
}

DBLaunch TabEditExtrasModel::getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport)
{
    return db->getLaunchFromParamIds(boosterRocket, upperBlock, spaceport);
}

QVector<qreal> TabEditExtrasModel::pricesToVector(QString prices)
{
    QVector<qreal> pricesVector;
    QStringList vals = prices.split(";");
    for (int i=0;i<vals.length();i++)
        pricesVector.append(vals[i].trimmed().toDouble());
    qDebug()<<pricesVector;
    return pricesVector;
}

int TabEditExtrasModel::getOrganizationId(QString name)
{
    return db->getOrganizationIdFromName(name);
}


int TabEditExtrasModel::getSpaceportId(QString name)
{
    return db->getSpaceportIdFromName(name);
}

void TabEditExtrasModel::updateOrganizationDB(int id, QString name)
{
    db->updateOrganizationDB(id, name);
}

void TabEditExtrasModel::updateSpaceportDB(int id, QString name)
{
    db->updateSpaceportDB(id, name);
}

void TabEditExtrasModel::deleteOrganization(int id)
{
    QVector<int> unitIds = db->getUnitIdsByOrganizationId(id);
    for (int i=0;i<unitIds.length();i++)
    {
        QString unitClass = db->getUnitClassById(unitIds[i]);
        if (unitClass=="РН")
        {
            db->deleteBoosterRocket(unitIds[i]);
            db->deleteLaunchByBoosterRocket(unitIds[i]);
        }

        else if (unitClass=="РБ")
        {
            db->deleteUpperBlock(unitIds[i]);
            db->deleteLaunchByUpperBlock(unitIds[i]);
        }
        else if (unitClass=="КА")
            db->deleteSpacecraft(unitIds[i]);
        db->deleteProjectWithUnitId(unitIds[i]);
        db->deleteUnit(unitIds[i]);
    }
    db->deleteOrganization(id);
}

void TabEditExtrasModel::deleteSpaceport(int id)
{
    QVector<int> unitIds = db->getUnitIdsBySpaceportId(id);
    for (int i=0;i<unitIds.length();i++)
    {
        QString unitClass = db->getUnitClassById(unitIds[i]);
        if (unitClass=="РН")
        {
            db->deleteBoosterRocket(unitIds[i]);
            db->deleteLaunchByBoosterRocket(unitIds[i]);
        }

        else if (unitClass=="РБ")
        {
            db->deleteUpperBlock(unitIds[i]);
            db->deleteLaunchByUpperBlock(unitIds[i]);
        }
        else if (unitClass=="КА")
            db->deleteSpacecraft(unitIds[i]);
        db->deleteProjectWithUnitId(unitIds[i]);
        db->deleteUnit(unitIds[i]);
    }
    QVector<int> launchIds = db->getLaunchIdsBySpaceportId(id);
    db->deleteLaunchBySpaceport(id);
    db->deleteSpaceport(id);
}

QVector<qreal> TabEditExtrasModel::getInflation()
{
    return db->getInflationPercents(2024,2040);
}

void TabEditExtrasModel::updateInflation(QVector<QPair<int,qreal>> values)
{
    for (int i=0;i<values.length();i++)
        db->updateInflation(values[i].first, values[i].second);
}

void TabEditExtrasModel::updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload, bool valid)
{
    int boosterRocketId = db->getUnitIdByName(boosterRocketName);
    int upperBlockId = db->getUnitIdByName(upperBlockName);
    int spaceportId = db->getSpaceportIdFromName(spaceportName);
    db->updateLaunchPricesByIds(boosterRocketId, upperBlockId, spaceportId,priceYear, prices, launchPrice, deliveryPrice, minPayload, maxPayload, valid);
}

QStringList TabEditExtrasModel::QVectorToQStringList(QVector <QString> vector)
{
    {
        QStringList result = {};
        for (int i=0;i<vector.length();i++)
        {
            result.append(vector[i]);
        }
        return result;
    }
}
