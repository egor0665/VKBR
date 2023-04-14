#ifndef TABPREDICTIONMODEL_H
#define TABPREDICTIONMODEL_H

#include <FileManager.h>
#include <FileProjectValue.h>
#include <MainModel.h>
#include <qstringlist.h>

const int INFLATIONMATRIXN = 20;

class TabPredictionModel
{

public:
    TabPredictionModel();
//    TabPredictionModel(MainModel* _mainModel);
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
    void saveToPdf(QString name, QVector<QVector<QString>> data, QVector<QString> values,  QVector<QPair<QVector<QString>,QString>> chartValues, int startYear, int endYear, QString filePath);

    void setUpValues();
    TabPredictionModel(database *db);
    QStringList QVectorToQStringList(QVector<QString> vector);
private:
//    MainModel* mainModel;
    database* db;
    PredictionModel predictionModel;
    FileManager *fileManager;
    qreal inflationMatrix[INFLATIONMATRIXN][INFLATIONMATRIXN];
    QPair<QVector<qreal>,int> pricesTextToVector(QString pricesString);
};


#endif // TABPREDICTIONMODEL_H
