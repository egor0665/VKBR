#ifndef TABCATALOGANDCOMPARISONMODEL_H
#define TABCATALOGANDCOMPARISONMODEL_H

#include <MainModel.h>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>

class TabCatalogAndComparisonModel
{
public:
    TabCatalogAndComparisonModel();
    TabCatalogAndComparisonModel(MainModel* _mainModel);
    QTreeWidget *navigationTreeWidget;

    QVector <QPair<QString,QString>> splitValues(QString values);
    QVector <QPair<QString,QString>> getUnitData(int unitId);
    int getUnitIdByName(QString unitName);
    QString getUnitImageFromId(int unitId);
    void createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    QTreeWidgetItem *addTreeRoot(QString name, QTreeWidget *treeWidget);
    QString classSelect(QString _class);
    QVector<QPair<QString,QStringList>> formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2);
    qreal getNumberFromString(QString line, int param = 0);

    QVector <QPair<QString,QString>> vectorUnitData(int unitId);
    QVector <QPair<QString,QString>> vectorBoosterRocketData(int unitId);
    QVector <QPair<QString,QString>> vectorUpperBlockData(int unitId);
private:
    MainModel* mainModel;
};

#endif // TABCATALOGANDCOMPARISONMODEL_H