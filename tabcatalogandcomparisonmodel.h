#ifndef TABCATALOGANDCOMPARISONMODEL_H
#define TABCATALOGANDCOMPARISONMODEL_H

#include <DataBase.h>
#include <FileManager.h>
#include <MainModel.h>
#include <QObject>
#include <QTreeWidget>
#include <QWidget>

class TabCatalogAndComparisonModel
{
public:
    TabCatalogAndComparisonModel();
    TabCatalogAndComparisonModel(DataBase* d);

    QVector <QPair<QString,QString>> splitValues(QString values);
    QVector<QVector <QPair<QString,QString>>> getUnitData(int unitId);
    int getUnitIdByName(QString unitName);
    QString getUnitImageFromId(int unitId);
    void createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    QTreeWidgetItem *addTreeRoot(QString name, QTreeWidget *treeWidget);
    QString classSelect(QString _class);
    QVector<QPair<QString,QStringList>> formCompareTable(QVector<QVector<QPair<QString,QString>>> values);
    qreal getNumberFromString(QString line, int param = 0);

    QVector <QPair<QString,QString>> vectorUnitData(int unitId);
    QVector<QVector <QPair<QString,QString>>> vectorBoosterRocketData(int unitId);
    QVector<QVector <QPair<QString,QString>>> vectorUpperBlockData(int unitId);
    QVector<QVector <QPair<QString,QString>>> vectorSpacecraftData(int unitId);
    QVector <QLineSeries*> createChartLineSeries(int unitNum, QVector <CompareValue> compareValues, QStringList unitNames);
    QBarSeries *createChartBarSeries(int unitNum, QVector <CompareValue> compareValues, QStringList unitNames);

    void saveToPdfCatalogTab(QString name, QImage image, QVector<QPair<QString,QString>> values, QVector<QPair<QString,QString>> physValues, QVector<QPair<QString,QString>> econValues, QString path);
    void saveToPdfComparisonTab(QVector<QString> names, QVector<QImage> images, QVector<QVector<QString>> values, QVector<QVector<QString>> compareValues, QVector<int> selectedValues1, QVector<int> selectedValues2, QChartView* chart1 , QChartView* chart2 ,QString filePath);
private:
    FileManager *fileManager;
    DataBase* db;
};

#endif // TABCATALOGANDCOMPARISONMODEL_H
