#ifndef TABCATALOGMODEL_H
#define TABCATALOGMODEL_H

#include <MainModel.h>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>

class TabCatalogModel
{
public:
    TabCatalogModel();
    TabCatalogModel(MainModel* _mainModel);
    QTreeWidget *navigationTreeWidget;

    void createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    QTreeWidgetItem *addTreeRoot(QString name, QTreeWidget *treeWidget);
    QString classSelect(QString _class);
private:
    MainModel* mainModel;
};

#endif // TABCATALOGMODEL_H
