#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QMainWindow>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <database.h>

class MainModel
{
public:
    MainModel();
    database db;


    QTreeWidget *navigationTreeWidget;

    //QTreeWidget* createNavigationTree(QTreeWidget *a);
    void createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot);

    QVector <QPair<QString,QString>> getUnitData(int unitId);
    int getUnitIdByName(QString unitName);
    QString getUnitImageFromId(int unitId);

    QVector<QPair<QString,QStringList>> formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2);
    QVector<QPair<QString,QStringList>> getUnitEconData(int unitId);

protected:
    QVector <QPair<QString,QString>> splitValues(QString values);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    QTreeWidgetItem *addTreeRoot(QString name, QTreeWidget *treeWidget);
    QString classSelect(QString _class);
    QVector <QPair<QString,QString>> vectorUnitData(int unitId);
    QVector <QPair<QString,QString>> vectorBoosterRocketData(int unitId);
    QVector <QPair<QString,QString>> vectorUpperBlockData(int unitId);

};

#endif // MAINMODEL_H
