#include "tabnewcraftmodel.h"
#include <QDebug>

TabEditCraftModel::TabEditCraftModel()
{

}

//TabNewCraftModel::TabNewCraftModel(MainModel *_mainModel)
//{
//    mainModel = _mainModel;
//}

TabEditCraftModel::TabEditCraftModel(DataBase *db)
{
    this->db = db;
}

QString TabEditCraftModel::addUnitToDB(
        QString unit_class,
        QString name,
        QString purpose,
        QString project,
        QString objective,
        QString work_status,
        QString developer,
        QString extra_developer,
        QString manufacturer,
        int launches,
        QString customer,
        int successful,
        QDateTime first_launch,
        QString first_launch_spaceport,
        QString financing_type,
        QString control_system_type,
        QString image_url,
        qreal price,
        int price_year,
        qreal maxPayload,
        qreal minPayload,
        qreal weight,
        qreal activeLifetime,
        QString physInfo,
        QString econInfo
        )
{
    bool proj;
    if (project == "Проектный") proj = true;
    else proj = false;
    int devId = db->getOrganizationIdFromName(developer);
    int extrDevId = db->getOrganizationIdFromName(extra_developer);
    int manId = db->getOrganizationIdFromName(manufacturer);
    int custId = db->getOrganizationIdFromName(customer);
    int spaceportId = db->getSpaceportIdFromName(first_launch_spaceport);
    DBUnit newUnit = DBUnit(-1,unit_class,name,purpose,
                            proj,objective,work_status,
                            devId,extrDevId,manId,launches,
                            custId,successful,first_launch,
                            spaceportId,financing_type,
                            control_system_type,image_url,
                            price,price_year);
    int newUnitId = db->addUnitToDBRetId(newUnit);

    if (unit_class == "РН")
    {
        DBBooster_rocket newBoosterRocket = DBBooster_rocket(newUnitId, maxPayload, minPayload, physInfo, econInfo);
        db->addBoosterRocketToDB(newBoosterRocket);
        int boosterRocketId = db->getUnitIdByName(name);
        QVector<int> upperBlockIds = db->getIdsFromTable("upper_block");
        QVector<int> spaceportIds = db->getIdsFromTable("spaceport");
        for (int i=0;i<upperBlockIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBLaunch tmpLaunch = DBLaunch(-1, boosterRocketId, upperBlockIds[i],spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                db->addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "РБ")
    {
        DBUpper_block newUpperBlock = DBUpper_block(newUnitId, physInfo, econInfo);
        db->addUpperBlockToDB(newUpperBlock);
        int upperBlockId = db->getUnitIdByName(name);
        QVector<int> boosterRocketIds = db->getIdsFromTable("booster_rocket");
        QVector<int> spaceportIds = db->getIdsFromTable("spaceport");
        for (int i=0;i<boosterRocketIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBLaunch tmpLaunch = DBLaunch(-1, boosterRocketIds[i], upperBlockId,spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                db->addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "КА")
    {
        DBSpacecraft newSpacecraft = DBSpacecraft(newUnitId, weight, activeLifetime, physInfo, econInfo);
        db->addSpacecraftToDB(newSpacecraft);

    }
    return "db.addUnitToDBRetId(newUnit);";
}

QString TabEditCraftModel::updateUnitDB(
        int id,
        QString unit_class,
        QString name,
        QString purpose,
        QString project,
        QString objective,
        QString work_status,
        QString developer,
        QString extra_developer,
        QString manufacturer,
        int launches,
        QString customer,
        int successful,
        QDateTime first_launch,
        QString first_launch_spaceport,
        QString financing_type,
        QString control_system_type,
        QString image_url,
        qreal price,
        int price_year,
        qreal maxPayload,
        qreal minPayload,
        qreal weight,
        qreal activeLifetime,
        QString physInfo,
        QString econInfo)
{
    bool proj;
    if (project == "Проектный") proj = true;
    else proj = false;
    int devId = db->getOrganizationIdFromName(developer);
    int extrDevId = db->getOrganizationIdFromName(extra_developer);
    int manId = db->getOrganizationIdFromName(manufacturer);
    int custId = db->getOrganizationIdFromName(customer);
    int spaceportId = db->getSpaceportIdFromName(first_launch_spaceport);

    DBUnit newUnit = DBUnit(id,unit_class,name,purpose,
                            proj,objective,work_status,
                            devId,extrDevId,manId,launches,
                            custId,successful,first_launch,
                            spaceportId,financing_type,
                            control_system_type,image_url,
                            price,price_year);
    int newUnitId;
    if (updateUnitImageChanged)
        newUnitId = db->updateUnitDBRetId(newUnit);
    else
        newUnitId = db->updateUnitDBNoImageRetId(newUnit);
    if (unit_class == "РН")
    {
        DBBooster_rocket newBoosterRocket = DBBooster_rocket(newUnitId, maxPayload, minPayload, physInfo, econInfo);
        db->updateBoosterRocketDB(newBoosterRocket);
        int boosterRocketId = db->getUnitIdByName(name);
        QVector<int> upperBlockIds = db->getIdsFromTable("upper_block");
        QVector<int> spaceportIds = db->getIdsFromTable("spaceport");
        for (int i=0;i<upperBlockIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBLaunch tmpLaunch = DBLaunch(-1, boosterRocketId, upperBlockIds[i],spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                db->addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "РБ")
    {
        DBUpper_block newUpperBlock = DBUpper_block(newUnitId, physInfo, econInfo);
        db->updateUpperBlockDB(newUpperBlock);
        int upperBlockId = db->getUnitIdByName(name);
        QVector<int> boosterRocketIds = db->getIdsFromTable("booster_rocket");
        QVector<int> spaceportIds = db->getIdsFromTable("spaceport");
        for (int i=0;i<boosterRocketIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBLaunch tmpLaunch = DBLaunch(-1, boosterRocketIds[i], upperBlockId,spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                db->addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "КА")
    {
        DBSpacecraft newSpacecraft = DBSpacecraft(newUnitId, weight, activeLifetime, physInfo, econInfo);
        db->updateSpacecraftDB(newSpacecraft);
    }
    return "db.addUnitToDBRetId(newUnit);";
}

DBUnit TabEditCraftModel::getUnitDataByName(QString unitName)
{
    return db->getUnitInfoFromName(unitName);
}

DBOrganization TabEditCraftModel::getOrganizationById(int organizationId)
{
    return db->getOrganizationInfoFromId(organizationId);
}

DBSpaceport TabEditCraftModel::getSpaceportById(int spaceportId)
{
    return db->getSpaceportInfoFromId(spaceportId);
}

DBBooster_rocket TabEditCraftModel::getBoosterRocketById(int boosterRocketId)
{
    return db->getBooster_rocketInfoFromId(boosterRocketId);
}

DBUpper_block TabEditCraftModel::getUpperBlockById(int upperBlockId)
{
    return db->getUpper_blockInfoFromId(upperBlockId);
}

DBSpacecraft TabEditCraftModel::getSpacecraftById(int spacecraftId)
{
    return db->getSpacecraftInfoFromId(spacecraftId);
}

void TabEditCraftModel::deleteSpacecraft(int unitId)
{
    QString unitClass = db->getUnitClassById(unitId);
    if (unitClass=="РН")
    {
        db->deleteLaunchByBoosterRocket(unitId);
        db->deleteBoosterRocket(unitId);
    }

    else if (unitClass=="РБ")
    {
        db->deleteLaunchByUpperBlock(unitId);
        db->deleteUpperBlock(unitId);
    }
    else if (unitClass=="КА")
    {
        db->deleteProjectWithUnitId(unitId);
        db->deleteSpacecraft(unitId);
    }
    db->deleteUnit(unitId);
}

bool TabEditCraftModel::getUpdateUnitImageChanged() const
{
    return updateUnitImageChanged;
}

void TabEditCraftModel::setUpdateUnitImageChanged(bool newUpdateUnitImageChanged)
{
    updateUnitImageChanged = newUpdateUnitImageChanged;
}
