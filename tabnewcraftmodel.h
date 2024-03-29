#ifndef TABNEWCRAFTMODEL_H
#define TABNEWCRAFTMODEL_H

#include <MainModel.h>
#include <qdatetime.h>
#include <qstring.h>

class TabEditCraftModel
{
public:
    TabEditCraftModel();
    QString addUnitToDB(QString unit_class,
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
            QString first_launch_spaceport_id,
            QString financing_type,
            QString control_system_type,
            QString image_url,
            qreal price,
            int price_year,
            qreal maxPayload = 0,
            qreal minPayload = 0,
            qreal weight = 0,
            qreal activeLifetime = 0,
            QString physInfo = "",
            QString econInfo = ""
            );
    QString updateUnitDB(int id,
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
            QString first_launch_spaceport_id,
            QString financing_type,
            QString control_system_type,
            QString image_url,
            qreal price,
            int price_year,
            qreal maxPayload = 0,
            qreal minPayload = 0,
            qreal weight = 0,
            qreal activeLifetime = 0,
            QString physInfo = "",
            QString econInfo = "");
    DBUnit getUnitDataByName(QString unitName);
    DBOrganization getOrganizationById(int organizationId);
    DBSpaceport getSpaceportById(int spaceportId);
    DBBooster_rocket getBoosterRocketById(int boosterRocketId);
    DBUpper_block getUpperBlockById(int upperBlockId);
    DBSpacecraft getSpacecraftById(int spacecraftId);
    void deleteSpacecraft(int unitId);
    bool getUpdateUnitImageChanged() const;
    void setUpdateUnitImageChanged(bool newUpdateUnitImageChanged);

    TabEditCraftModel(DataBase *db);
private:
    DataBase* db;
    bool updateUnitImageChanged;
};

#endif // TABNEWCRAFTMODEL_H
