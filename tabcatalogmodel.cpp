#include "tabcatalogmodel.h"
#include <QDebug>

TabCatalogModel::TabCatalogModel()
{

}

TabCatalogModel::TabCatalogModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

void TabCatalogModel::createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot)
{
    navigatiorMenuRoot->setText(0, "Каталог");
    QVector <QPair<QString,QString>> units = mainModel->db.getUnitClassesAndNames();
    qDebug() << units;
    QString lastclass = "";
    QVector <QString> nameArray;

    for (int i=0;i < units.size();i++){
        QString _class = units[i].first;
        QString _name = units[i].second;

        if (lastclass!=_class){
            if (!nameArray.empty()){
                addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
            }
            nameArray.clear();
            lastclass = _class;
        }
        nameArray.append(_name);

    }
    addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
    return;
}

void TabCatalogModel::addTreeChild(QTreeWidgetItem *parent,
                              QString name, QVector <QString> child_array)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    for (int i=0; i<child_array.size();i++){
        addTreeChild2(treeItem, child_array[i]);
    }

}
void TabCatalogModel::addTreeChild2(QTreeWidgetItem *parent,
                               QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
}

QString TabCatalogModel::classSelect(QString _class)
{
    qDebug() << _class;
    QString resultClass;
    if (_class == "РН")
        resultClass = "Ракеты-носители";
    else if (_class == "РБ")
        resultClass = "Разгонные блоки";
    else if (_class == "ПГК")
        resultClass = "Пилотируемые и грузовые космические корабли/аппара";
    else if (_class == "КАС")
        resultClass = "Космические аппараты связи, вещания и ретрансляции, поиска и спасения";
    else
        resultClass = _class;
    qDebug() << _class << resultClass << endl;
    return resultClass;
}
