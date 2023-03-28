#ifndef TABPREDICTIONMODEL_H
#define TABPREDICTIONMODEL_H

#include <FileManager.h>
#include <FileProjectValue.h>
#include <MainModel.h>
#include <qstringlist.h>

class TabPredictionModel
{
public:
    TabPredictionModel();
    TabPredictionModel(MainModel* _mainModel);
    QStringList getNamesFromTableStringList(QString tableName);
    int projectModelAddProject(QString projectName);
    QStringList getValidLaunchesNamesStringList();
    int projectModelGetProjectNumber(QString projectName);
    void projectModelRemoveProject(QString projectName);
    int projectModelGetUnitLifetime(QString projectName);
    QVector<QVector<QPair<QString, QString> > > predictPrices(QString projectName, QVector<QVector<int>> yearsValues, QVector<QString> boosterRocketValues, bool brChanged, int column);
    void saveToFile(QVector<FileProjectValue> saveValues, QString filePath);
    QVector<int> fileRowTextToVector(QString rowString);
    QVector<FileProjectValue> loadFromFile(QString filePath);
    void projectModelClear();
    void saveToPdf(QString name, QVector<QVector<QString>> data, QVector<QString> values, int startYear, int endYear, QString filePath);
private:
    MainModel* mainModel;
    PredictionModel predictionModel;
    FileManager fileManager;
    QPair<QVector<qreal>,int> pricesTextToVector(QString pricesString);
};


#endif // TABPREDICTIONMODEL_H
