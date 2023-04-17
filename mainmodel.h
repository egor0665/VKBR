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
    DataBase db;
    QVector <QString> getNamesFromTable(QString tableName);
    QStringList getNamesFromTableStringList(QString tableName);
    QStringList QVectorToQStringList(QVector <QString> vector);
    QString login(QString name, QString password);
    const QString &getUserRole() const;
    void setUserRole(const QString &newUserRole);

    DataBase *getDBLink();
protected:
    QString userRole;
};

#endif // MAINMODEL_H
