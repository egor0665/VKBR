#ifndef TABNEWEXTRASMODEL_H
#define TABNEWEXTRASMODEL_H

#include <MainModel.h>
#include <qstringlist.h>

class TabEditExtrasModel
{
public:
    TabEditExtrasModel();
    void addOrganizationToDB(QString name);
    void addSpaceportToDB(QString name);
    QStringList getUnitNamesByTypeStringList(QString type);
    DBLaunch getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport);
    QVector<qreal> pricesToVector(QString prices);
    int getOrganizationId(QString name);
    int getSpaceportId(QString name);
    void updateOrganizationDB(int id, QString name);
    void updateSpaceportDB(int id, QString name);
    void deleteOrganization(int id);
    void deleteSpaceport(int id);
    QVector<qreal> getInflation();
    void updateInflation(QVector<QPair<int,qreal>> values);
    TabEditExtrasModel(DataBase *db);
    void updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload, bool valid);
    QStringList QVectorToQStringList(QVector<QString> vector);
private:
//    MainModel* mainModel;
    DataBase* db;
};

#endif // TABNEWEXTRASMODEL_H
