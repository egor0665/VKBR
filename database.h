#ifndef DATABASE_H
#define DATABASE_H

#include <organization.h>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <spaceport.h>
#include <unit.h>
#include <booster_rocket.h>
#include <Upper_block.h>

class database
{
public:
    database();
    bool createConnection();
    QVector <QPair<QString,QString>> getUnitClassesAndNames();
    QStringList getUnitNames();
    Unit getUnitInfoFromName(QString name);
    Unit getUnitInfoFromId(int unitId);
    Organization getOrganizationInfoFromId(int id);
    Spaceport getSpaceportInfoFromId(int id);
    Booster_rocket getBooster_rocketInfoFromId(int id);
    int getUnitIdFromName(QString name);
    QString getUnitImageFromId(int unitId);
    QString getUnitClassById(int unitId);

    Upper_block getUpper_blockInfoFromId(int unitId);
};

#endif // DATABASE_H
