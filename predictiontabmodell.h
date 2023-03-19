#ifndef PREDICTIONTABMODELL_H
#define PREDICTIONTABMODELL_H

#include <MainModel.h>
#include <qstringlist.h>



class PredictionTabModel
{
public:
    PredictionTabModel();
    QStringList getNamesFromTableStringList(QString tableName);
    int projectModelAddProject(QString projectName);
    QStringList getValidLaunchesNamesStringList();
    int projectModelGetProjectNumber(QString projectName);
    void projectModelRemoveProject(QString projectName);
    int projectModelGetUnitLifetime(QString projectName);
    QVector<QVector<QPair<QString, QString> > > predictPrices(QString projectName, QVector<QVector<int>> yearsValues, QVector<QString> boosterRocketValues, bool brChanged, int column);
private:
    MainModel mainModel;
    PredictionModel predictionModel;
    QPair<QVector<qreal>,int> pricesTextToVector(QString pricesString);
};

#endif // PREDICTIONTABMODELL_H
