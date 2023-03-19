#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QMainWindow>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <database.h>
#include <comparevalue.h>
#include <PredictionModel.h>

class MainModel
{
public:
    MainModel();
    database db;
    QVector <QString> getNamesFromTable(QString tableName);
    QStringList getNamesFromTableStringList(QString tableName);
    QStringList QVectorToQStringList(QVector <QString> vector);
//    QVector <QString> getTableDescriptions();
//    QStringList getTableDescriptionsStringList();

//    int getTableColumnCount(QString tableName);
//    QVector <QString> getTableColumnNames(QString tableName);
//    QStringList getTableColumnNamesStringList(QString tableName);
//    QVector <QVector<QString>> getValuesFromTable(QString tableName, int valuesNum);
//    QString updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange);

//    QString addUnitToDB(

//            QString unit_class,
//            QString name,
//            QString purpose,
//            QString project,
//            QString objective,
//            QString work_status,
//            QString developer,
//            QString extra_developer,
//            QString manufacturer,
//            int launches,
//            QString customer,
//            int successful,
//            QDateTime first_launch,
//            QString first_launch_spaceport_id,
//            QString financing_type,
//            QString control_system_type,
//            QString image_url,
//            qreal price,
//            int price_year,
//            qreal maxPayload = 0,
//            qreal minPayload = 0,
//            qreal weight = 0,
//            QString physInfo = "",
//            QString econInfo = ""
//            );


//    void addOrganizationToDB(QString name);
//    void addSpaceportToDB(QString name);
    //void addProjectToDB(QString name, QString type, QString unit_name);
//    QVector<QVector<qreal>> getProjectPricesFromName(QString projectName);
//    void updateProjectInfo(QString projectName, QVector<qreal> pre_prices, QVector<qreal> first_unit_prices, QVector<qreal> last_unit_prices, QVector<qreal> post_prices, QVector<qreal> serial_prices);



//    QStringList getUnitNamesByTypeStringList(QString type);
//    DBlaunch getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport);
//    QVector<qreal> pricesToVector(QString prices);

    void updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload);

protected:
//    QVector <QPair<QString,QString>> splitValues(QString values);
//    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
//    void addTreeChild2(QTreeWidgetItem *parent, QString name);
//    QTreeWidgetItem *addTreeRoot(QString name, QTreeWidget *treeWidget);
//    QString classSelect(QString _class);
//    QVector <QPair<QString,QString>> vectorUnitData(int unitId);
//    QVector <QPair<QString,QString>> vectorBoosterRocketData(int unitId);
//    QVector <QPair<QString,QString>> vectorUpperBlockData(int unitId);

};

#endif // MAINMODEL_H
