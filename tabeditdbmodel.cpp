#include "tabeditdbmodel.h"
#include <QDebug>

TabEditDBModel::TabEditDBModel()
{

}
//TabEditDBModel::TabEditDBModel(MainModel *_mainModel)
//{
//    mainModel = _mainModel;
//}

TabEditDBModel::TabEditDBModel(DataBase *db)
{
    this->db = db;
}

QStringList TabEditDBModel::getTableDescriptionsStringList()
{
    return  QVectorToQStringList(getTableDescriptions());
}
QVector <QString> TabEditDBModel::getTableDescriptions()
{
    return db->getTableDescriptions();
}

int TabEditDBModel::getTableColumnCount(QString tableName)
{
    return db->getTableColumnCount(tableName);
}

QVector <QString> TabEditDBModel::getTableColumnNames(QString tableName)
{
    return db->getTableColumnNames(tableName);
}

QStringList TabEditDBModel::getTableColumnNamesStringList(QString tableName)
{
    return QVectorToQStringList(getTableColumnNames(tableName));
}

//QString TabEditDBModel::getUnitImageFromId(int unitId)
//{
//    return db->getUnitImageFromId(unitId);
//}

QVector <QVector<QString>> TabEditDBModel::getValuesFromTable(QString tableName, int valuesNum)
{
    return db->getValuesFromTable(tableName, valuesNum);
}

QString TabEditDBModel::updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange)
{
    return db->updateDataInTable(tableName, dbValuesToChange);
}

QStringList TabEditDBModel::QVectorToQStringList(QVector<QString> vector)
{
    QStringList result = {};
    for (int i=0;i<vector.length();i++)
    {
        result.append(vector[i]);
    }
    return result;
}

