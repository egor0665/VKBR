#include "DBProject.h"
#include "DBspacecraft.h"
#include "database.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QLibrary>
#include <QMap>
#include <QMessageBox>
#include <QSqlQuery>
#include<QtSql/QSqlError>
#include<string.h>
#include<QVariant>
#include<QDebug>
#include<QPair>
#include <DBunit.h>
#include <DBorganization.h>
#include <DBspaceport.h>
#include <DBbooster_rocket.h>
#include <dbChangeValue.h>
#include <DBlaunch.h>
#include <QDateTime>

database::database()
{

}
bool database::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("CATALOG");
    db.setUserName("postgres");
    db.setPassword("ADMIN");
    if (!db.open()){
        //QMessageBox::warning(0,"Ошибка подключения к БД","Ошибка подключения к БД");
         QMessageBox::warning(0,"Ошибка подключения к БД",db.lastError().text());
        return false;
    }
    else
    {
        QMessageBox::information(0,"Успешное подключения к БД","Успешное подключения к БД");
        return true;
    }
}
QVector<QPair<QString,QString>> database::getUnitClassesAndNames()
{
    QVector<QPair<QString,QString>> unit_vector = QVector<QPair<QString,QString>>();
    QSqlQuery query;
    query.exec("SELECT unit_class, name FROM unit ORDER BY unit_class");
    while (query.next()) {
           QString _unit_class = query.value(0).toString().trimmed();
           QString _name = query.value(1).toString().trimmed();
           unit_vector.append(QPair<QString,QString>(_unit_class,_name));
           qDebug() << _unit_class << _name << endl;
       }
    return unit_vector;
}

QVector <QString> database::getUnitNames()
{
    QVector <QString> name_vector;
    QSqlQuery query;
    query.exec("SELECT name FROM unit ORDER BY unit_class");
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           name_vector.append(_name);
           qDebug() <<  _name << endl;
       }
    return name_vector;
}

DBUnit database::getUnitInfoFromName(QString name)
{
    /*unit
     * id
     * unit_class
     * name
     * purpose
     * project
     * objective
     * work_status
     * developer_id
     * extra_developer_id
     * manufacturer_id
     * launches
     * customer_id
     * successful
     * first_launch
     * first_launch_spaceport_id
     * financing_type
     * control_system_type
     * image_url
     * price
     * price_year
     * */

    QSqlQuery query;
    query.exec("SELECT id, unit_class, name, purpose, project, objective, work_status, developer_id, extra_developer_id, manufacturer_id, launches, customer_id, successful, first_launch, first_launch_spaceport_id, financing_type, control_system_type, image_url, price, price_year FROM unit WHERE unit.name LIKE '" + name + "%'");
    query.next();
    //qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    qDebug() << "IMGSSS" << query.value(17);

    DBUnit tmpUnit = DBUnit(query.value(0).toInt(),
                        query.value(1).toString().trimmed(),
                        query.value(2).toString().trimmed(),
                        query.value(3).toString().trimmed(),
                        query.value(4).toBool(),
                        query.value(5).toString().trimmed(),
                        query.value(6).toString().trimmed(),
                        query.value(7).toInt(),
                        query.value(8).toInt(),
                        query.value(9).toInt(),
                        query.value(10).toInt(),
                        query.value(11).toInt(),
                        query.value(12).toInt(),
                        QDateTime::fromString(query.value(13).toString().trimmed(), "yyyy-MM-dd hh:mm:ss"),
                        query.value(14).toInt(),
                        query.value(15).toString().trimmed(),
                        query.value(16).toString().trimmed(),
                        query.value(17).toString(),
                        query.value(18).toDouble(),
                        query.value(19).toInt());

    return tmpUnit;
}

DBUnit database::getUnitInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT id, unit_class, name, purpose, project, objective, work_status, developer_id, extra_developer_id, manufacturer_id, launches, customer_id, successful, first_launch, first_launch_spaceport_id, financing_type, control_system_type, image_url, price, price_year FROM unit WHERE unit.id = " + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    DBUnit tmpUnit = DBUnit(query.value(0).toInt(),
                        query.value(1).toString().trimmed(),
                        query.value(2).toString().trimmed(),
                        query.value(3).toString().trimmed(),
                        query.value(4).toBool(),
                        query.value(5).toString().trimmed(),
                        query.value(6).toString().trimmed(),
                        query.value(7).toInt(),
                        query.value(8).toInt(),
                        query.value(9).toInt(),
                        query.value(10).toInt(),
                        query.value(11).toInt(),
                        query.value(12).toInt(),
                        QDateTime::fromString(query.value(13).toString().trimmed(), "yyyy-MM-dd hh:mm:ss"),
                        query.value(14).toInt(),
                        query.value(15).toString().trimmed(),
                        query.value(16).toString().trimmed(),
                        query.value(17).toString().trimmed(),
                        query.value(18).toDouble(),
                        query.value(19).toInt());
    return tmpUnit;
    qDebug() << query.value(0);
}

int database::getUnitIdByName(QString name)
{
    QSqlQuery query;
    query.exec("SELECT id FROM unit WHERE unit.name LIKE '" + name + "%'");
    query.next();
    qDebug() <<query.value(0);
    return query.value(0).toInt();
}

QString database::getUnitImageFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT image_url FROM unit WHERE unit.id = " + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0);
    return query.value(0).toString().trimmed();
}

DBOrganization database::getOrganizationInfoFromId(int id)
{
    QSqlQuery query;
    query.exec("SELECT id, name FROM organization WHERE organization.id=" + QString::number(id));
    query.next();
    qDebug() <<query.value(0)<<query.value(1);
    DBOrganization tmpOrganization = DBOrganization(query.value(0).toInt(),
                        query.value(1).toString().trimmed());
    return tmpOrganization;
}

DBSpaceport database::getSpaceportInfoFromId(int id)
{
    QSqlQuery query;
    query.exec("SELECT id, name FROM spaceport WHERE spaceport.id=" + QString::number(id));
    query.next();
    qDebug() <<query.value(0)<<query.value(1);
    DBSpaceport tmpSpaceport = DBSpaceport(query.value(0).toInt(),
                        query.value(1).toString().trimmed());
    return tmpSpaceport;
}

DBBooster_rocket database::getBooster_rocketInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT id, max_payload, min_payload, phys_info, econ_info FROM booster_rocket WHERE id=" + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4);
    DBBooster_rocket tmpBooster_rocket = DBBooster_rocket(query.value(0).toInt(),
                                                 query.value(1).toInt(),
                                                 query.value(2).toInt(),
                                                 query.value(4).toString().trimmed(),
                                                 query.value(5).toString().trimmed());
    return tmpBooster_rocket;
}
DBUpper_block database::getUpper_blockInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT id, phys_info, econ_info FROM upper_block WHERE id=" + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2);
    DBUpper_block tmpUpper_block = DBUpper_block(query.value(0).toInt(),
                                                 query.value(1).toString().trimmed(),
                                                 query.value(2).toString().trimmed());
    return tmpUpper_block;
}

QString database::getUnitClassById(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT unit_class FROM unit WHERE id=" + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0);
    QString unitClass  = query.value(0).toString().trimmed();
    return unitClass;
}

QVector<QString> database::getOrganizationNames()
{
    QVector<QString> organization_vector = QVector<QString>();
    QSqlQuery query;
    query.exec("SELECT name FROM organization ORDER BY name");
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           organization_vector.append(_name);
           qDebug() << _name << endl;
       }
    return organization_vector;
}

QVector<QString> database::getNamesFromTable(QString tableName)
{
    QVector<QString> name_vector = QVector<QString>();
    QSqlQuery query;
    query.exec("SELECT name FROM "+ tableName+ " ORDER BY name");
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           name_vector.append(_name);
           qDebug() << _name << endl;
       }
    return name_vector;
}

QVector <QString> database::getTableNames()
{
    QVector<QString> table_vector = QVector<QString>();
    QSqlQuery query;
    query.exec("SELECT name FROM tables WHERE editable = true");
    qDebug() << query.lastError();
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           table_vector.append(_name);
           qDebug() << _name << endl;
       }
    return table_vector;
}

QVector <QString> database::getTableDescriptions()
{
    QVector<QString> description_vector = QVector<QString>();
    QSqlQuery query;
    query.exec("SELECT table_name from INFORMATION_SCHEMA.tables WHERE table_schema='public'");
    qDebug() << query.lastError();
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           description_vector.append(_name);
           qDebug() << _name << endl;
       }
    return description_vector;
}

QVector <QString> database::getTableColumnNames(QString tableName)
{
    QVector<QString> name_vector = QVector<QString>();
    QSqlQuery query;
    query.exec("SELECT column_name FROM INFORMATION_SCHEMA.columns WHERE table_schema = 'public' AND table_name = '"+tableName+"'");
    qDebug() << query.lastError();
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           name_vector.append(_name);
           qDebug() << _name << endl;
       }
    return name_vector;
}

int database::getTableColumnCount(QString tableName)
{
    int count = 0;
    QSqlQuery query;
    query.exec("SELECT count(*) FROM INFORMATION_SCHEMA.columns WHERE table_name = '"+tableName+"'");
    qDebug() << query.lastError();
    while (query.next()) {
           count = query.value(0).toString().trimmed().toInt();
           qDebug() << count << endl;
       }
    return count;
}

QVector<QVector<QString>> database::getValuesFromTable(QString tableName, int valuesNum)
{
    QVector<QVector<QString>> values;
    QSqlQuery query;
    query.exec("SELECT * FROM "+ tableName);
    while (query.next()) {
        QVector<QString> tmpVal;
        for (int i=0;i<valuesNum;i++)
            tmpVal.append(query.value(i).toString().trimmed());
        values.append(tmpVal);
       }
    return values;
}

QString database::updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange)
{
    QSqlQuery query;
    for (int i=0;i<dbValuesToChange.length();i++){
        QString queryString = "UPDATE public."+ tableName +" SET " + dbValuesToChange[i].getHeader() +" = '" + dbValuesToChange[i].getValue() + "' WHERE id = '" + dbValuesToChange[i].getId()+"' ORDER BY id";
        qDebug() <<queryString;
        query.exec(queryString);
    }
    return query.lastError().text();
}

int database::getOrganizationIdFromName(QString organizationName)
{
    int organizationId;
    QSqlQuery query;
    query.exec("SELECT id FROM organization WHERE name LIKE '" + organizationName+ "%'");
    while (query.next()) {
           organizationId = query.value(0).toString().trimmed().toInt();
       }
    return organizationId;
}

int database::getSpaceportIdFromName(QString spaceportName)
{
    int spaceportId;
    QSqlQuery query;
    query.exec("SELECT id FROM spaceport WHERE name LIKE '" + spaceportName + "%'");
    while (query.next()) {
           spaceportId = query.value(0).toString().trimmed().toInt();
       }
    return spaceportId;
}

int database::addUnitToDBRetId(DBUnit unit)
{
    QSqlQuery query;
    query.exec("INSERT INTO unit ( unit_class, name, purpose, project, objective, work_status, developer_id, extra_developer_id, manufacturer_id, launches, customer_id, successful, first_launch, first_launch_spaceport_id, financing_type, control_system_type, image_url, price, price_year) VALUES ('" +
               unit.unit_class() + "', '" +
               unit.name() + "', '" +
               unit.purpose() + "', " +
               QString::number(unit.project()) + ", '" +
               unit.objective() + "', '" +
               unit.work_status() + "', " +
               QString::number(unit.developer_id()) + ", " +
               QString::number(unit.extra_developer_id()) + ", " +
               QString::number(unit.manufacturer_id()) + ", " +
               QString::number(unit.launches()) + ", " +
               QString::number(unit.customer_id()) + ", " +
               QString::number(unit.successful()) + ", '" +
               unit.first_launch().toString("yyyy-MM-dd HH:mm:ss") + "', " +
               QString::number(unit.first_launch_spaceport_id()) + ", '" +
               unit.financing_type() + "', '" +
               unit.control_system_type() + "', '" +
               unit.image_url() + "', " +
               QString::number(unit.price()) + ", " +
               QString::number(unit.price_year())+") RETURNING id");
    qDebug() << query.lastError();
    query.next();
    return query.value(0).toString().trimmed().toInt();

}
int database::updateUnitDBRetId(DBUnit unit)
{
    QSqlQuery query;
    query.exec("UPDATE public.unit SET unit_class = '" + unit.unit_class() +
               "', name = '" + unit.name() +
               "', purpose = '" + unit.purpose() +
               "', project = " + QString::number(unit.project()) +
               ", objective = '" + unit.objective() +
               "', work_status = '" + unit.work_status() +
               "', developer_id = " + QString::number(unit.developer_id()) +
               ", extra_developer_id = " + QString::number(unit.extra_developer_id()) +
               ", manufacturer_id = " + QString::number(unit.manufacturer_id()) +
               ", launches = " + QString::number(unit.launches()) +
               ", successful = " + QString::number(unit.successful()) +
               ", first_launch = '" + unit.first_launch().toString("yyyy-MM-dd HH:mm:ss") +
               "', first_launch_spaceport_id = " + QString::number(unit.first_launch_spaceport_id()) +
               ", financing_type = '" + unit.financing_type() +
               "', control_system_type = '" + unit.control_system_type() +
               "', image_url = '" + unit.image_url() +
               "', price = " + QString::number(unit.price()) +
               ", price_year = " + QString::number(unit.price_year()) +
               " WHERE id = " + QString::number(unit.id())+ " RETURNING id");
    qDebug() << query.lastError();
    query.next();
    return query.value(0).toString().trimmed().toInt();

}


void database::addBoosterRocketToDB(DBBooster_rocket boosterRocket)
{
    QSqlQuery query;
    query.exec("INSERT INTO booster_rocket ( id, max_payload, min_payload, phys_info, econ_info ) VALUES (" +
               QString::number(boosterRocket.id()) + ", " +
               QString::number(boosterRocket.max_payload()) + ", " +
               QString::number(boosterRocket.min_payload()) + ", '" +
               boosterRocket.phys_info() + "', '" +
               boosterRocket.econ_info()+"')");
    qDebug() << query.lastError();
    return;
}

void database::updateBoosterRocketDB(DBBooster_rocket boosterRocket)
{
    QSqlQuery query;
    query.exec("UPDATE public.booster_rocket SET  max_payload = " + QString::number(boosterRocket.max_payload()) +
               ", min_payload = " + QString::number(boosterRocket.min_payload()) +
               ", phys_info = '" + boosterRocket.phys_info() +
               "', econ_info = '" + boosterRocket.econ_info() +
               "' WHERE id = " + QString::number(boosterRocket.id()));
    qDebug() << query.lastError();
    return;
}

void database::addUpperBlockToDB(DBUpper_block upperBlock)
{
    QSqlQuery query;
    query.exec("INSERT INTO upper_block ( id, phys_info, econ_info ) VALUES (" +
               QString::number(upperBlock.id()) + ", '" +
               upperBlock.phys_info() + "', '" +
               upperBlock.econ_info()+"')");
    qDebug() << query.lastError();
    return;
}
void database::updateUpperBlockDB(DBUpper_block upperBlock)
{
    QSqlQuery query;
    query.exec("UPDATE public.upper_block SET phys_info = '" + upperBlock.phys_info() +
               "', econ_info = '" + upperBlock.econ_info() +
               "' WHERE id = " + QString::number(upperBlock.id()));
    qDebug() << query.lastError();
    return;
}
void database::addSpacecraftToDB(DBSpacecraft spacecraft)
{
    QSqlQuery query;
    query.exec("INSERT INTO spacecraft ( id, weight, active_lifetime, phys_info, econ_info ) VALUES (" +
               QString::number(spacecraft.id()) + ", " +
               QString::number(spacecraft.weight()) + ", '" +
               QString::number(spacecraft.active_lifetime()) + ", '" +
               spacecraft.phys_info() + "', '" +
               spacecraft.econ_info()+"')");
    qDebug() << query.lastError();
    return;
}
void database::updateSpacecraftDB(DBSpacecraft spacecraft)
{
    QSqlQuery query;
    query.exec("UPDATE public.spacecraft SET weight = " + QString::number(spacecraft.weight()) +
               ", active_lifetime = " + QString::number(spacecraft.active_lifetime()) +
               ", phys_info = '" + spacecraft.phys_info() +
               "', econ_info = '" + spacecraft.econ_info() +
               "' WHERE id = " + QString::number(spacecraft.id()));
    qDebug() << query.lastError();
    return;
}

void database::addOrganoizationToDB(DBOrganization newOrganization)
{
    QSqlQuery query;
    query.exec("INSERT INTO organization ( name ) VALUES ('" +
               newOrganization.name() +"')");
    qDebug() << query.lastError();
    return;
}

void database::addSpaceportToDB(DBSpaceport newSpaceport)
{
    QSqlQuery query;
    query.exec("INSERT INTO spaceport ( name ) VALUES ('" +
               newSpaceport.name() +"')");
    qDebug() << query.lastError();
    return;
}

void database::addProjectToDB(DBProject newProject)
{
    QSqlQuery query;
    query.exec("INSERT INTO project ( name, type, unit_id, pre_prices, first_unit_prices, last_unit_prices, post_prices, serial_prices ) VALUES ('" +
               newProject.name() + "', '" +
               newProject.type() + "', " +
               QString::number(newProject.unit_id())+ ", '" +
               newProject.pre_prices() + "', '" +
               newProject.first_unit_prices() + "', '" +
               newProject.last_unit_prices() + "', '" +
               newProject.post_prices() + "', '" +
               newProject.serial_prices() + "')");
    qDebug() << query.lastError();
    return;
}



DBProject database::getProjectInfoFromName(QString projectName)
{
    QSqlQuery query;
    query.exec("SELECT id, name, type, unit_id, pre_prices, first_unit_prices, last_unit_prices, post_prices, serial_prices FROM project WHERE project.name LIKE '" + projectName + "%'");
    query.next();
    //qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    DBProject tmpProject = DBProject(query.value(0).toInt(),
                        query.value(1).toString().trimmed(),
                        query.value(2).toString().trimmed(),
                        query.value(3).toInt(),
                        query.value(4).toString().trimmed(),
                        query.value(5).toString().trimmed(),
                        query.value(6).toString().trimmed(),
                        query.value(7).toString().trimmed(),
                        query.value(8).toString().trimmed());
    return tmpProject;
}

DBProject database::getProjectInfoFromId (int projectId)
{
    QSqlQuery query;
    query.exec("SELECT id, name, type, unit_id, pre_prices, first_unit_prices, last_unit_prices, post_prices, serial_prices FROM project WHERE project.id =" + QString::number(projectId));
    query.next();
    //qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    DBProject tmpProject = DBProject(query.value(0).toInt(),
                        query.value(1).toString().trimmed(),
                        query.value(2).toString().trimmed(),
                        query.value(3).toInt(),
                        query.value(4).toString().trimmed(),
                        query.value(5).toString().trimmed(),
                        query.value(6).toString().trimmed(),
                        query.value(7).toString().trimmed(),
                        query.value(8).toString().trimmed());
    return tmpProject;
}

void database::updateProjectPricesByName(QString projectName, QString new_pre_prices, QString new_first_unit_prices, QString new_last_unit_prices, QString new_post_prices, QString new_serial_prices)
{
    QSqlQuery query;
    QString queryString = "UPDATE public.project SET pre_prices = '" + new_pre_prices + "', first_unit_prices = '" + new_first_unit_prices + "',last_unit_prices = '" + new_last_unit_prices + "', post_prices = '" + new_post_prices + "', serial_prices = '" + new_serial_prices + "' WHERE name LIKE '" + projectName + "%'";
    qDebug() <<queryString;
    query.exec(queryString);
    qDebug() << query.lastError().text();
}

QVector <int> database::getIdsFromTable(QString tableName)
{
    QVector <int>  ids;
    QSqlQuery query;
    query.exec("SELECT id FROM " + tableName);
    while (query.next()) {
           ids.append(query.value(0).toString().trimmed().toInt());
       }
    return ids;
}

void database::addLaunchInformation(DBlaunch launch)
{
    QSqlQuery query;
    query.exec("INSERT INTO launch (booster_rocket_id, upper_block_id, spaceport_id, price_year, prices, launch_price, delivery_price, min_payload, max_payload, valid) VALUES (" +
                QString::number(launch.booster_rocket_id()) + ", " +
                QString::number(launch.upper_block_id()) + ", " +
                QString::number(launch.spaceport_id()) + ", " +
                QString::number(launch.price_year()) + ", '" +
                launch.prices() + "', " +
                QString::number(launch.launch_price()) + ", " +
                QString::number(launch.delivery_price()) + ", " +
                QString::number(launch.min_payload()) + ", " +
                QString::number(launch.max_payload()) + ", " +
                " false)");
    qDebug() << query.lastError();
    return;
}

QVector <QString> database::getUnitNamesByType(QString type)
{
    QVector <QString>  names;
    QSqlQuery query;
    query.exec("SELECT name FROM unit WHERE unit_class LIKE '" + type + "%'");
    while (query.next()) {
           names.append(query.value(0).toString().trimmed());
       }
    return names;
}

DBlaunch database::getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport)
{
    DBlaunch launch;
    QSqlQuery query;
    query.exec("SELECT lnch.id, lnch.booster_rocket_id, lnch.upper_block_id, lnch.spaceport_id, lnch.price_year, lnch.prices, lnch.launch_price, lnch.delivery_price, lnch.min_payload, lnch.max_payload "
               "FROM launch lnch, unit unt1, unit unt2, spaceport spcprt "
               "WHERE unt1.name LIKE '" + boosterRocket + "%' AND lnch.booster_rocket_id = unt1.id "
               "AND unt2.name LIKE '" + upperBlock + "%' AND lnch.upper_block_id = unt2.id "
               "AND spcprt.name LIKE '" + spaceport + "%' AND lnch.spaceport_id = spcprt.id");
    while (query.next()) {
        launch = DBlaunch(query.value(0).toString().trimmed().toInt(),
                          query.value(1).toString().trimmed().toInt(),
                          query.value(2).toString().trimmed().toInt(),
                          query.value(3).toString().trimmed().toInt(),
                          query.value(4).toString().trimmed().toInt(),
                          query.value(5).toString().trimmed(),
                          query.value(6).toString().trimmed().toDouble(),
                          query.value(7).toString().trimmed().toDouble(),
                          query.value(8).toString().trimmed().toDouble(),
                          query.value(9).toString().trimmed().toDouble());
    }
    qDebug() << query.lastError();
    return launch;
}

DBlaunch database::getLaunchById(int id)
{
    DBlaunch launch;
    QSqlQuery query;
    query.exec("SELECT id, booster_rocket_id, upper_block_id, spaceport_id, price_year, prices, launch_price, delivery_price, min_payload, max_payload "
               "FROM launch "
               "WHERE id =" + QString::number(id));
    while (query.next()) {
        launch = DBlaunch(query.value(0).toString().trimmed().toInt(),
                          query.value(1).toString().trimmed().toInt(),
                          query.value(2).toString().trimmed().toInt(),
                          query.value(3).toString().trimmed().toInt(),
                          query.value(4).toString().trimmed().toInt(),
                          query.value(5).toString().trimmed(),
                          query.value(6).toString().trimmed().toDouble(),
                          query.value(7).toString().trimmed().toDouble(),
                          query.value(8).toString().trimmed().toDouble(),
                          query.value(9).toString().trimmed().toDouble());
    }
    qDebug() << query.lastError();
    return launch;
}

int database::getSpacecraftLifetimeById(int unitId)
{
    int unitLifetime;
    QSqlQuery query;
    query.exec("SELECT active_lifetime FROM spacecraft WHERE id = "  + QString::number(unitId));
    while (query.next()) {
           unitLifetime = query.value(0).toString().trimmed().toInt();
       }
    return unitLifetime;
}

void database::updateLaunchPricesByIds(int boosterRocketId, int upperBlockId, int spaceportId, int price_year, QString prices, qreal launch_price, qreal delivery_price, qreal min_payload, qreal max_payload)
{
    QSqlQuery query;
    QString queryString = "UPDATE public.launch SET price_year = " + QString::number(price_year) + ", prices = '" + prices + "', launch_price = " + QString::number(launch_price) + ", delivery_price = " + QString::number(delivery_price) + ", min_payload = " + QString::number(min_payload) + ", max_payload = " + QString::number(max_payload) + ", valid = true WHERE booster_rocket_id = " + QString::number(boosterRocketId) + " AND upper_block_id = " + QString::number(upperBlockId) + " AND spaceport_id = " + QString::number(spaceportId);
    qDebug() <<queryString;
    query.exec(queryString);
    qDebug() << query.lastError().text();
}

QVector <QVector<int>> database::getValidLaunchesIds()
{
    QVector <QVector<int>> resultValues;
    QSqlQuery query;
    query.exec("SELECT booster_rocket_id, upper_block_id, spaceport_id FROM launch WHERE valid = true");
    while (query.next()) {
            QVector<int> ids;
           ids.append(query.value(0).toString().trimmed().toInt());
           ids.append(query.value(1).toString().trimmed().toInt());
           ids.append(query.value(2).toString().trimmed().toInt());
           resultValues.append(ids);
       }
    return resultValues;
}

QString database::getNameFromTableById(QString tableName, int id)
{
    QString name;
    QSqlQuery query;
    query.exec("SELECT name FROM " + tableName + " WHERE id = " + QString::number(id));
    while (query.next())
    {
        name = query.value(0).toString().trimmed();
    }
    return name;
}

qreal database::getSpacecraftWeightByProjectName(QString projectName)
{
    qreal weight;
    QSqlQuery query;
    query.exec("SELECT sc.weight FROM project pr, spacecraft sc WHERE pr.name LIKE '" + projectName + "%' AND pr.unit_id = sc.id");
    while (query.next())
    {
        weight = query.value(0).toString().trimmed().toDouble();
    }

    return weight;
}

QVector<qreal> database::getInflationPercents(int startYear, int endYear)
{
    QVector<qreal> inflationPercents;
    QSqlQuery query;
    query.exec("SELECT percent FROM inflation WHERE year >= " + QString::number(startYear) + " AND year <= " + QString::number(endYear) + " ORDER BY year");
    while (query.next())
    {
        inflationPercents.append(query.value(0).toString().trimmed().toDouble());
    }

    return inflationPercents;
}

DBSpacecraft database::getSpacecraftInfoFromId(int spacecraftId)
{
    QSqlQuery query;
    query.exec("SELECT id, weight, active_lifetime, phys_info, econ_info FROM spacecraft WHERE id=" + QString::number(spacecraftId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2);
    DBSpacecraft tmpSpacecraft = DBSpacecraft(query.value(0).toInt(),
                                              query.value(1).toDouble(),
                                              query.value(2).toDouble(),
                                              query.value(3).toString().trimmed(),
                                              query.value(4).toString().trimmed());
    return tmpSpacecraft;
}
//QString database::getSpaceportsInfoByUnitId(int unitId)
//{
//    QSqlQuery query;
//    query.exec("SELECT s.name FROM spaceport s, u_s us, unit u WHERE u.id=us.id and s.id=us.id and u.id=" + QString::number(unitId));
//    query.next();
//    qDebug() <<query.value(0)<<query.value(1)<<query.value(2);
//    Upper_block tmpUpper_block = Upper_block(query.value(0).toInt(),
//                                                 query.value(1).toString().trimmed(),
//                                                 query.value(2).toString().trimmed());
//    return tmpUpper_block;
//}
