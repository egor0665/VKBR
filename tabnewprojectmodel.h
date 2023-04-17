#ifndef TABNEWPROJECTMODEL_H
#define TABNEWPROJECTMODEL_H

#include <MainModel.h>
#include <qstring.h>

class TabEditProjectModel
{
public:
    TabEditProjectModel();
    void addProjectToDB(QString name, QString type, QString unit_name);
    QVector<QVector<qreal>> getProjectPricesFromName(QString projectName);
    void updateProjectInfo(QString projectName, QVector<qreal> pre_prices, QVector<qreal> first_unit_prices, QVector<qreal> last_unit_prices, QVector<qreal> post_prices, QVector<qreal> serial_prices);
    TabEditProjectModel(DataBase *db);
private:
    DataBase* db;
};

#endif // TABNEWPROJECTMODEL_H
