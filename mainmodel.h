#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QMainWindow>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <database.h>
#include <comparevalue.h>
#include <PredictionModel.h>
#include <ChartManager.h>

class MainModel
{
public:
    MainModel();
    database db;
    ChartManager chartManager;
    QVector <QString> getNamesFromTable(QString tableName);
    QStringList getNamesFromTableStringList(QString tableName);
    QStringList QVectorToQStringList(QVector <QString> vector);
    void updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload, bool valid);

    QString login(QString name, QString password);
    const QString &getUserRole() const;
    void setUserRole(const QString &newUserRole);

protected:
    QString userRole;
};

#endif // MAINMODEL_H
