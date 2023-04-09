#include "tabnewextrasmodel.h"
#include <QDebug>

TabNewExtrasModel::TabNewExtrasModel()
{

}

TabNewExtrasModel::TabNewExtrasModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

void TabNewExtrasModel::addOrganizationToDB(QString name)
{
    DBOrganization newOrganization = DBOrganization(-1, name);
    mainModel->db.addOrganoizationToDB(newOrganization);
}

void TabNewExtrasModel::addSpaceportToDB(QString name)
{
    DBSpaceport newSpaceport = DBSpaceport(-1, name);
    mainModel->db.addSpaceportToDB(newSpaceport);

    int spaceportId = mainModel->db.getSpaceportIdFromName(name);
    QVector<int> boosterRocketIds = mainModel->db.getIdsFromTable("booster_rocket");
    QVector<int> upperBlockIds = mainModel->db.getIdsFromTable("upper_block");
    for (int i=0;i<boosterRocketIds.length();i++)
        for (int j=0;j<upperBlockIds.length();j++)
        {
            DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketIds[i], upperBlockIds[j],spaceportId,2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0,false);
            mainModel->db.addLaunchInformation(tmpLaunch);
        }
}

//QStringList TabNewExtrasModel::getNamesFromTableStringList(QString tableName)
//{
//     return QVectorToQStringList(mainModel->getNamesFromTable(tableName));
//}

QStringList TabNewExtrasModel::getUnitNamesByTypeStringList(QString type)
{
    return mainModel->QVectorToQStringList(mainModel->db.getUnitNamesByType(type));
}

DBlaunch TabNewExtrasModel::getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport)
{
    return mainModel->db.getLaunchFromParamIds(boosterRocket, upperBlock, spaceport);
}

QVector<qreal> TabNewExtrasModel::pricesToVector(QString prices)
{
    QVector<qreal> pricesVector;
    QStringList vals = prices.split(";");
    for (int i=0;i<vals.length();i++)
        pricesVector.append(vals[i].trimmed().toDouble());
    qDebug()<<pricesVector;
    return pricesVector;
}

int TabNewExtrasModel::getOrganizationId(QString name)
{
    return mainModel->db.getOrganizationIdFromName(name);
}


int TabNewExtrasModel::getSpaceportId(QString name)
{
    return mainModel->db.getSpaceportIdFromName(name);
}

void TabNewExtrasModel::updateOrganizationDB(int id, QString name)
{
    mainModel->db.updateOrganizationDB(id, name);
}

void TabNewExtrasModel::updateSpaceportDB(int id, QString name)
{
    mainModel->db.updateSpaceportDB(id, name);
}
