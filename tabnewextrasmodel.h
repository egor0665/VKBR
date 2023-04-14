#ifndef TABNEWEXTRASMODEL_H
#define TABNEWEXTRASMODEL_H

#include <MainModel.h>
#include <qstringlist.h>

class TabNewExtrasModel
{
public:
    TabNewExtrasModel();
//    TabNewExtrasModel(MainModel *_mainModel);
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
    QVector<qreal> getInflation();
    void updateInflation(QVector<QPair<int,qreal>> values);
    TabNewExtrasModel(database *db);
    void updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload, bool valid);
    QStringList QVectorToQStringList(QVector<QString> vector);
private:
//    MainModel* mainModel;
    database* db;
};

#endif // TABNEWEXTRASMODEL_H
