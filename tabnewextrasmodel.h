#ifndef TABNEWEXTRASMODEL_H
#define TABNEWEXTRASMODEL_H

#include <MainModel.h>
#include <qstringlist.h>



class TabNewExtrasModel
{
public:
    TabNewExtrasModel();
    TabNewExtrasModel(MainModel *_mainModel);
    void addOrganizationToDB(QString name);
    void addSpaceportToDB(QString name);
    QStringList getUnitNamesByTypeStringList(QString type);
    DBlaunch getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport);
    QVector<qreal> pricesToVector(QString prices);
    int getOrganizationId(QString name);
    int getSpaceportId(QString name);
    void updateOrganizationDB(int id, QString name);
    void updateSpaceportDB(int id, QString name);
    void deleteOrganization(int id);
    void deleteSpaceport(int id);
private:
    MainModel* mainModel;
};

#endif // TABNEWEXTRASMODEL_H
