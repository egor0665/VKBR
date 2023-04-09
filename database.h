#ifndef DATABASE_H
#define DATABASE_H

#include "DBProject.h"
#include "DBUser.h"
#include "DBspacecraft.h"

#include <DBorganization.h>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <DBspaceport.h>
#include <DBunit.h>
#include <DBbooster_rocket.h>
#include <DBUpper_block.h>
#include <dbChangeValue.h>
#include <DBlaunch.h>

class database
{
public:
    database();
    bool createConnection();
    QVector <QPair<QString,QString>> getUnitClassesAndNames();
    QVector <QString> getUnitNames();
    DBUnit getUnitInfoFromName(QString name);
    DBUnit getUnitInfoFromId(int unitId);
    DBOrganization getOrganizationInfoFromId(int id);
    DBSpaceport getSpaceportInfoFromId(int id);
    DBBooster_rocket getBooster_rocketInfoFromId(int id);
    int getUnitIdByName(QString name);
    QString getUnitImageFromId(int unitId);
    QString getUnitClassById(int unitId);
    QVector <QString> getOrganizationNames();
    QVector <QString> getNamesFromTable(QString tableName);

    DBUpper_block getUpper_blockInfoFromId(int unitId);

    QVector <QString> getTableNames();
    QVector <QString> getTableDescriptions();

    int getTableColumnCount(QString tableName);
    QVector <QString> getTableColumnNames(QString tableName);
    QVector <QString> getDataFromTable(QString tableName);

    QVector<QVector<QString>> getValuesFromTable(QString tableName, int valuesNum);
    QString updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange);
    int getOrganizationIdFromName(QString organizationName);
    int getSpaceportIdFromName(QString spaceportName);
    int addUnitToDBRetId(DBUnit unit);

    void addBoosterRocketToDB(DBBooster_rocket boosterRocket);
    void addUpperBlockToDB(DBUpper_block upperBlock);
    void addOrganoizationToDB(DBOrganization newOrganization);
    void addSpaceportToDB(DBSpaceport newSpaceport);
    void addProjectToDB(DBProject newProject);
    void addSpacecraftToDB(DBSpacecraft newSpacecraft);
    DBProject getProjectInfoFromName(QString projectName);
    void updateProjectPricesByName(QString projectName, QString new_pre_prices, QString new_first_unit_prices, QString new_last_unit_prices, QString new_post_prices, QString new_serial_prices);
    QVector <int> getIdsFromTable(QString tableName);
    void addLaunchInformation(DBlaunch launch);
    QVector <QString> getUnitNamesByType(QString type);
    DBlaunch getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport);
    int getSpacecraftLifetimeById(int unitId);
    void updateLaunchPricesByIds(int boosterRocketId, int upperBlockId, int spaceportId, int price_year, QString prices, qreal launch_price, qreal delivery_price, qreal min_payload, qreal max_payload, bool valid);
    QVector<QVector<int>> getValidLaunchesIds();
    QString getNameFromTableById(QString tableName, int id);
    qreal getSpacecraftWeightByProjectName(QString projectName);
    QVector<qreal> getInflationPercents(int startYear, int endYear);
    DBSpacecraft getSpacecraftInfoFromId(int spacecraftId);
    int updateUnitDBRetId(DBUnit unit);
    void updateSpacecraftDB(DBSpacecraft spacecraft);
    void updateUpperBlockDB(DBUpper_block upperBlock);
    void updateBoosterRocketDB(DBBooster_rocket boosterRocket);
    DBProject getProjectInfoFromId(int projectId);
    DBlaunch getLaunchById(int id);
    void deleteUnit(int unitId);
    void deleteBoosterRocket(int unitId);
    void deleteSpacecraft(int unitId);
    void deleteUpperBlock(int unitId);
    void deleteProjectWithUnitId(int unitId);
    void deleteLaunchByBoosterRocket(int unitId);
    void deleteLaunchByUpperBlock(int unitId);
    void updateOrganizationDB(int id, QString name);
    void updateSpaceportDB(int id, QString name);
    int getUserIdByName(QString name);
    DBUser getUserById(int userId);
    void addUserToDB(DBUser user);
    void updateUserDB(DBUser user);
    void deleteUserFromDB(int userId);
};

#endif // DATABASE_H
