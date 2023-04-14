#include "DBProject.h"
#include "tabnewprojectmodel.h"
#include <QDebug>

TabNewProjectModel::TabNewProjectModel()
{

}

//TabNewProjectModel::TabNewProjectModel(MainModel *_mainModel)
//{
//    mainModel = _mainModel;
//}

TabNewProjectModel::TabNewProjectModel(database *db)
{
    this->db = db;
}

void TabNewProjectModel::addProjectToDB(QString name, QString type, QString unit_name)
{
    int unit_id = db->getUnitIdByName(unit_name);
    DBProject newProject = DBProject(-1, name, type, unit_id, "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;");
    db->addProjectToDB(newProject);
}

QVector<QVector<qreal>> TabNewProjectModel::getProjectPricesFromName(QString projectName)
{
    DBProject currentProject = db->getProjectInfoFromName(projectName);
    QVector<qreal> pre_prices, post_prices, first_unit_prices, last_unit_prices, serial_prices;
    QStringList preVals = currentProject.pre_prices().split(";");
    QStringList firstUnitVals = currentProject.first_unit_prices().split(";");
    QStringList lastUnitVals = currentProject.last_unit_prices().split(";");
    QStringList postVals = currentProject.post_prices().split(";");
    QStringList serialVals = currentProject.serial_prices().split(";");
    for (int i=0;i<preVals.length();i++){
        pre_prices.append(preVals[i].trimmed().toDouble());
        first_unit_prices.append(firstUnitVals[i].trimmed().toDouble());
        last_unit_prices.append(lastUnitVals[i].trimmed().toDouble());
        post_prices.append(postVals[i].trimmed().toDouble());
        serial_prices.append(serialVals[i].trimmed().toDouble());
    }
    QVector<QVector<qreal>> results;
    results.append(pre_prices);
    results.append(first_unit_prices);
    results.append(last_unit_prices);
    results.append(post_prices);
    results.append(serial_prices);
    return results;
}

void TabNewProjectModel::updateProjectInfo(QString projectName, QVector<qreal> pre_prices, QVector<qreal> first_unit_prices, QVector<qreal> last_unit_prices, QVector<qreal> post_prices, QVector<qreal> serial_prices)
{
    QString new_pre_prices="", new_first_unit_prices="", new_last_unit_prices="", new_post_prices="", new_serial_prices="";
    for (int i=0;i<pre_prices.length();i++)
    {
        new_pre_prices += QString::number(pre_prices[i]) + ";";
        new_first_unit_prices += QString::number(first_unit_prices[i]) + ";";
        new_last_unit_prices += QString::number(last_unit_prices[i]) + ";";
        new_post_prices += QString::number(post_prices[i]) + ";";
        new_serial_prices += QString::number(serial_prices[i]) + ";";
    }
    qDebug()<<new_pre_prices<<new_first_unit_prices<<new_last_unit_prices<<new_post_prices<<new_serial_prices;
    db->updateProjectPricesByName(projectName,new_pre_prices,new_first_unit_prices, new_last_unit_prices, new_post_prices,new_serial_prices);
}
