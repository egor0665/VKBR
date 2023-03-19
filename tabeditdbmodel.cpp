#include "tabeditdbmodel.h"
#include <QDebug>

TabEditDBModel::TabEditDBModel()
{

}
TabEditDBModel::TabEditDBModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}
QStringList TabEditDBModel::getTableDescriptionsStringList()
{
    return  mainModel->QVectorToQStringList(getTableDescriptions());
}
QVector <QString> TabEditDBModel::getTableDescriptions()
{
    return mainModel->db.getTableDescriptions();
}

int TabEditDBModel::getTableColumnCount(QString tableName)
{
    return mainModel->db.getTableColumnCount(tableName);
}

QVector <QString> TabEditDBModel::getTableColumnNames(QString tableName)
{
    return mainModel->db.getTableColumnNames(tableName);
}

QStringList TabEditDBModel::getTableColumnNamesStringList(QString tableName)
{
    return mainModel->QVectorToQStringList(getTableColumnNames(tableName));
}

//QString TabEditDBModel::getUnitImageFromId(int unitId)
//{
//    return mainModel->db.getUnitImageFromId(unitId);
//}

QVector <QVector<QString>> TabEditDBModel::getValuesFromTable(QString tableName, int valuesNum)
{
    return mainModel->db.getValuesFromTable(tableName, valuesNum);
}

QString TabEditDBModel::updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange)
{
    return mainModel->db.updateDataInTable(tableName, dbValuesToChange);
}

