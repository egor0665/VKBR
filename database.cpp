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
#include <unit.h>
#include <organization.h>
#include <spaceport.h>
#include <booster_rocket.h>

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

QStringList database::getUnitNames()
{
    QStringList name_vector;
    QSqlQuery query;
    query.exec("SELECT name FROM unit ORDER BY unit_class");
    while (query.next()) {
           QString _name = query.value(0).toString().trimmed();
           name_vector.append(_name);
           qDebug() <<  _name << endl;
       }
    return name_vector;
}

Unit database::getUnitInfoFromName(QString name)
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
    query.exec("SELECT * FROM unit WHERE unit.name LIKE '%" + name + "%'");
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    Unit tmpUnit = Unit(query.value(0).toInt(),
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
                        QDateTime(),
                        query.value(13).toInt(),
                        query.value(14).toString().trimmed(),
                        query.value(15).toString().trimmed(),
                        query.value(16).toString().trimmed(),
                        query.value(17).toReal(),
                        query.value(18).toInt());
    return tmpUnit;
    qDebug() << query.value(0);
}

Unit database::getUnitInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT * FROM unit WHERE unit.id = " + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9)<<query.value(10)<<query.value(11)<<query.value(12)<<query.value(13)<<query.value(14)<<query.value(15)<<query.value(16)<<query.value(17)<<query.value(18);
    Unit tmpUnit = Unit(query.value(0).toInt(),
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
                        QDateTime(),
                        query.value(13).toInt(),
                        query.value(14).toString().trimmed(),
                        query.value(15).toString().trimmed(),
                        query.value(16).toString().trimmed(),
                        query.value(17).toReal(),
                        query.value(18).toInt());
    return tmpUnit;
    qDebug() << query.value(0);
}

int database::getUnitIdFromName(QString name)
{
    QSqlQuery query;
    query.exec("SELECT id FROM unit WHERE unit.name LIKE '%" + name + "%'");
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

Organization database::getOrganizationInfoFromId(int id)
{
    QSqlQuery query;
    query.exec("SELECT * FROM organization WHERE organization.id=" + QString::number(id));
    query.next();
    qDebug() <<query.value(0)<<query.value(1);
    Organization tmpOrganization = Organization(query.value(0).toInt(),
                        query.value(1).toString().trimmed());
    return tmpOrganization;
}

Spaceport database::getSpaceportInfoFromId(int id)
{
    QSqlQuery query;
    query.exec("SELECT * FROM spaceport WHERE spaceport.id=" + QString::number(id));
    query.next();
    qDebug() <<query.value(0)<<query.value(1);
    Spaceport tmpSpaceport = Spaceport(query.value(0).toInt(),
                        query.value(1).toString().trimmed());
    return tmpSpaceport;
}

Booster_rocket database::getBooster_rocketInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT * FROM booster_rocket WHERE id=" + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4);
    Booster_rocket tmpBooster_rocket = Booster_rocket(query.value(0).toInt(),
                                                 query.value(1).toString().trimmed(),
                                                 query.value(2).toInt(),
                                                 query.value(3).toString().trimmed(),
                                                 query.value(4).toString().trimmed());
    return tmpBooster_rocket;
}
Upper_block database::getUpper_blockInfoFromId(int unitId)
{
    QSqlQuery query;
    query.exec("SELECT * FROM upper_block WHERE id=" + QString::number(unitId));
    query.next();
    qDebug() <<query.value(0)<<query.value(1)<<query.value(2);
    Upper_block tmpUpper_block = Upper_block(query.value(0).toInt(),
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
