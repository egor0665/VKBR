#ifndef TABEDITDBMODEL_H
#define TABEDITDBMODEL_H

#include <MainModel.h>
#include <dbChangeValue.h>
#include <qstring.h>



class TabEditDBModel
{
public:
    TabEditDBModel();
    TabEditDBModel(DataBase *db);
    QVector <QString> getTableDescriptions();
    QStringList getTableDescriptionsStringList();
    int getTableColumnCount(QString tableName);
    QVector <QString> getTableColumnNames(QString tableName);
    QStringList getTableColumnNamesStringList(QString tableName);
    QVector <QVector<QString>> getValuesFromTable(QString tableName, int valuesNum);
    QString updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange);
    QStringList QVectorToQStringList(QVector <QString> vector);
private:
    DataBase* db;

};

#endif // TABEDITDBMODEL_H
