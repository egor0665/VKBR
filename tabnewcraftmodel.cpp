#include "tabnewcraftmodel.h"
#include <QDebug>

TabNewCraftModel::TabNewCraftModel()
{

}

TabNewCraftModel::TabNewCraftModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

QString TabNewCraftModel::addUnitToDB(
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
    int devId = mainModel->db.getOrganizationIdFromName(developer);
    int extrDevId = mainModel->db.getOrganizationIdFromName(extra_developer);
    int manId = mainModel->db.getOrganizationIdFromName(manufacturer);
    int custId = mainModel->db.getOrganizationIdFromName(customer);
    int spaceportId = mainModel->db.getSpaceportIdFromName(first_launch_spaceport);
    DBUnit newUnit = DBUnit(-1,unit_class,name,purpose,
                            proj,objective,work_status,
                            devId,extrDevId,manId,launches,
                            custId,successful,first_launch,
                            spaceportId,financing_type,
                            control_system_type,image_url,
                            price,price_year);
    int newUnitId = mainModel->db.addUnitToDBRetId(newUnit);

    if (unit_class == "РН")
    {
        DBBooster_rocket newBoosterRocket = DBBooster_rocket(newUnitId, maxPayload, minPayload, physInfo, econInfo);
        mainModel->db.addBoosterRocketToDB(newBoosterRocket);
        int boosterRocketId = mainModel->db.getUnitIdByName(name);
        QVector<int> upperBlockIds = mainModel->db.getIdsFromTable("upper_block");
        QVector<int> spaceportIds = mainModel->db.getIdsFromTable("spaceport");
        for (int i=0;i<upperBlockIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketId, upperBlockIds[i],spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                mainModel->db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "РБ")
    {
        DBUpper_block newUpperBlock = DBUpper_block(newUnitId, physInfo, econInfo);
        mainModel->db.addUpperBlockToDB(newUpperBlock);
        int upperBlockId = mainModel->db.getUnitIdByName(name);
        QVector<int> boosterRocketIds = mainModel->db.getIdsFromTable("booster_rocket");
        QVector<int> spaceportIds = mainModel->db.getIdsFromTable("spaceport");
        for (int i=0;i<boosterRocketIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketIds[i], upperBlockId,spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                mainModel->db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "КА")
    {
        DBSpacecraft newSpacecraft = DBSpacecraft(newUnitId, weight, activeLifetime, physInfo, econInfo);
        mainModel->db.addSpacecraftToDB(newSpacecraft);
    }
    return "db.addUnitToDBRetId(newUnit);";
}

QString TabNewCraftModel::updateUnitDB(
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
    int devId = mainModel->db.getOrganizationIdFromName(developer);
    int extrDevId = mainModel->db.getOrganizationIdFromName(extra_developer);
    int manId = mainModel->db.getOrganizationIdFromName(manufacturer);
    int custId = mainModel->db.getOrganizationIdFromName(customer);
    int spaceportId = mainModel->db.getSpaceportIdFromName(first_launch_spaceport);

    DBUnit newUnit = DBUnit(id,unit_class,name,purpose,
                            proj,objective,work_status,
                            devId,extrDevId,manId,launches,
                            custId,successful,first_launch,
                            spaceportId,financing_type,
                            control_system_type,image_url,
                            price,price_year);
    int newUnitId;
    if (updateUnitImageChanged)
        newUnitId = mainModel->db.updateUnitDBRetId(newUnit);
    else
        newUnitId = mainModel->db.updateUnitDBNoImageRetId(newUnit);
    if (unit_class == "РН")
    {
        DBBooster_rocket newBoosterRocket = DBBooster_rocket(newUnitId, maxPayload, minPayload, physInfo, econInfo);
        mainModel->db.updateBoosterRocketDB(newBoosterRocket);
        int boosterRocketId = mainModel->db.getUnitIdByName(name);
        QVector<int> upperBlockIds = mainModel->db.getIdsFromTable("upper_block");
        QVector<int> spaceportIds = mainModel->db.getIdsFromTable("spaceport");
        for (int i=0;i<upperBlockIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketId, upperBlockIds[i],spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                mainModel->db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "РБ")
    {
        DBUpper_block newUpperBlock = DBUpper_block(newUnitId, physInfo, econInfo);
        mainModel->db.updateUpperBlockDB(newUpperBlock);
        int upperBlockId = mainModel->db.getUnitIdByName(name);
        QVector<int> boosterRocketIds = mainModel->db.getIdsFromTable("booster_rocket");
        QVector<int> spaceportIds = mainModel->db.getIdsFromTable("spaceport");
        for (int i=0;i<boosterRocketIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketIds[i], upperBlockId,spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0, false);
                mainModel->db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "КА")
    {
        DBSpacecraft newSpacecraft = DBSpacecraft(newUnitId, weight, activeLifetime, physInfo, econInfo);
        mainModel->db.updateSpacecraftDB(newSpacecraft);
    }
    return "db.addUnitToDBRetId(newUnit);";
}

DBUnit TabNewCraftModel::getUnitDataByName(QString unitName)
{
    return mainModel->db.getUnitInfoFromName(unitName);
}

DBOrganization TabNewCraftModel::getOrganizationById(int organizationId)
{
    return mainModel->db.getOrganizationInfoFromId(organizationId);
}

DBSpaceport TabNewCraftModel::getSpaceportById(int spaceportId)
{
    return mainModel->db.getSpaceportInfoFromId(spaceportId);
}

DBBooster_rocket TabNewCraftModel::getBoosterRocketById(int boosterRocketId)
{
    return mainModel->db.getBooster_rocketInfoFromId(boosterRocketId);
}

DBUpper_block TabNewCraftModel::getUpperBlockById(int upperBlockId)
{
    return mainModel->db.getUpper_blockInfoFromId(upperBlockId);
}

DBSpacecraft TabNewCraftModel::getSpacecraftById(int spacecraftId)
{
    return mainModel->db.getSpacecraftInfoFromId(spacecraftId);
}

void TabNewCraftModel::deleteSpacecraft(int unitId)
{
    QString unitClass = mainModel->db.getUnitClassById(unitId);
    if (unitClass=="РН")
    {
        mainModel->db.deleteBoosterRocket(unitId);
        mainModel->db.deleteLaunchByBoosterRocket(unitId);
    }

    else if (unitClass=="РБ")
    {
        mainModel->db.deleteUpperBlock(unitId);
        mainModel->db.deleteLaunchByUpperBlock(unitId);
    }
    else if (unitClass=="КА")
        mainModel->db.deleteSpacecraft(unitId);
    mainModel->db.deleteProjectWithUnitId(unitId);
    mainModel->db.deleteUnit(unitId);
}

bool TabNewCraftModel::getUpdateUnitImageChanged() const
{
    return updateUnitImageChanged;
}

void TabNewCraftModel::setUpdateUnitImageChanged(bool newUpdateUnitImageChanged)
{
    updateUnitImageChanged = newUpdateUnitImageChanged;
}
