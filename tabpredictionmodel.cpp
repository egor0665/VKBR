#include "tabpredictionmodel.h"

#include <qstringlist.h>
#include <QDebug>
#include <FileProjectValue.h>
#include <QFile>

TabPredictionModel::TabPredictionModel()
{

}

TabPredictionModel::TabPredictionModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

QStringList TabPredictionModel::getNamesFromTableStringList(QString tableName)
{
     return mainModel->QVectorToQStringList(mainModel->getNamesFromTable(tableName));
}

int TabPredictionModel::projectModelAddProject(QString projectName)
{
    DBProject project = mainModel->db.getProjectInfoFromName(projectName);
    QPair<QVector<qreal>,int> pricesTmp;

    pricesTmp = pricesTextToVector(project.pre_prices());
    QVector <qreal> prePrices = pricesTmp.first;
    int prePricesStartYear = pricesTmp.second;

    pricesTmp = pricesTextToVector(project.first_unit_prices());
    QVector <qreal> firstUnitPrices = pricesTmp.first;
    int firstUnitStartYear = pricesTmp.second;

    pricesTmp = pricesTextToVector(project.last_unit_prices());
    QVector <qreal> lastUnitPrices = pricesTmp.first;
    int lastUnitStartYear = pricesTmp.second;

    pricesTmp = pricesTextToVector(project.post_prices());
    QVector <qreal> postPrices = pricesTmp.first;
    int postPricesStartYear = pricesTmp.second;

    pricesTmp = pricesTextToVector(project.serial_prices());
    QVector <qreal> serialPrices = pricesTmp.first;
    int serialPricesStartYear = pricesTmp.second;
    qDebug()<< prePrices << prePricesStartYear<<firstUnitPrices<<firstUnitStartYear<<lastUnitPrices<<lastUnitStartYear<<postPrices<<postPricesStartYear<<serialPrices<<serialPricesStartYear;
    int projectLifetime = -1;
    if (project.type()!="Другое")
    {
        projectLifetime = mainModel->db.getSpacecraftLifetimeById(project.unit_id());
    }

    ProjectSet newProjectSet = ProjectSet(project.type(),
                                          project.name(),
                                          project.id(),
                                          project.unit_id(),
                                          projectLifetime,
                                          prePrices,
                                          prePricesStartYear,
                                          firstUnitPrices,
                                          firstUnitStartYear,
                                          lastUnitPrices,
                                          lastUnitStartYear,
                                          postPrices,
                                          postPricesStartYear,
                                          serialPrices,
                                          serialPricesStartYear);

    int index = predictionModel.addProject(newProjectSet) * 7;
    if (project.type() == "Связь")
        index += 1;
    else if (project.type() == "ДЗЗ")
        index += 2;
    else if (project.type() == "ФКИ")
        index += 3;
    if (project.type() == "Другое")
        index += 4;
    return index;
}

QStringList TabPredictionModel::getValidLaunchesNamesStringList()
{
    QVector<QVector<int>> ids = mainModel->db.getValidLaunchesIds();
    QVector<QString> names;
    for (int i=0;i<ids.length();i++)
    {
        QString boosterRocketName = mainModel->db.getNameFromTableById("unit",ids[i][0]);
        QString upperBlockName = mainModel->db.getNameFromTableById("unit",ids[i][1]);
        QString spaceportName = mainModel->db.getNameFromTableById("spaceport",ids[i][2]);
        names.append(boosterRocketName + " с " + upperBlockName + " (" + spaceportName+ ")");
    }

    return mainModel->QVectorToQStringList(names);
}

int TabPredictionModel::projectModelGetProjectNumber(QString projectName)
{
    QString projectType = predictionModel.getProjectType(projectName);
    int index = predictionModel.getProjectNumber(projectName) * 7;
    if (projectType == "Связь")
        index += 1;
    else if (projectType == "ДЗЗ")
        index += 2;
    else if (projectType == "ФКИ")
        index += 3;
    if (projectType == "Другое")
        index += 4;
    return index;
}

void TabPredictionModel::projectModelRemoveProject(QString projectName)
{
    predictionModel.removeProject(projectName);
}

int TabPredictionModel::projectModelGetUnitLifetime(QString projectName)
{
    return predictionModel.getUnitLifetime(projectName);
}

QVector<QVector<QPair<QString,QString>>> TabPredictionModel::predictPrices(QString projectName, QVector<QVector<int>> yearsValues, QVector<QString> boosterRocketValues, bool brChanged, int column)
{
    ProjectSet currentProject = predictionModel.getProjectSetByName(projectName);
    int unitLifeTime = predictionModel.getUnitLifetime(projectName);
    QVector<QVector<QPair<QString,QString>>> tmp;
    QVector <qreal> unitPrices ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    QVector <qreal> boosterRocketPrices ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    QVector <int> okrYears = yearsValues[0];
    QVector <int> serialYears = yearsValues[1];
    QVector <int> blockValues = yearsValues[2];
    bool firstUnit = true;
    int difPreFirstUnit = currentProject.getFirstUnitStartYear() - currentProject.getPrePricesStartYear();
    int difPostLastUnit = -1* (currentProject.getPostPricesStartYear() + currentProject.getPostPrices().length() - currentProject.getLastUnitStartYear() - currentProject.getLastUnitPrices().length() );
    qDebug() << difPreFirstUnit;

    QVector<QPair<QString,QString>> unitResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};
    QVector<QPair<QString,QString>> serialUnitResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};
    QVector<QPair<QString,QString>> blockResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};
    QVector<QPair<QString,QString>> boosterRocketResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};
    QVector<QPair<QString,QString>> unitPricesResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};
    QVector<QPair<QString,QString>> rocketPricesResultValues = {{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"},{"0","n"}};

    int lastUnitYear = 0;
    for (int i=okrYears.length()-1;i > -1;i--)
        if (okrYears[i]>0)
        {
            lastUnitYear = i;
            break;
        }
    QVector<qreal> inflationPercents = mainModel->db.getInflationPercents(2024,2040);
    qDebug() << inflationPercents;
    qreal inflationMatrix [inflationPercents.length()][inflationPercents.length()];

    for (int i=0;i<inflationPercents.length();i++)
            inflationMatrix[i][i] = 1;
    QString debugMatrix = "";
    for (int i=0;i<inflationPercents.length();i++)
    {
        for (int j=i+1;j<inflationPercents.length();j++)
        {
            inflationMatrix[i][j] = inflationMatrix[i][j-1] * inflationPercents[j];
        }
    }

    for (int i=0;i<inflationPercents.length();i++)
    {
        for (int j=i-1;j>=0;j--)
        {
            inflationMatrix[i][j] = 1/(inflationMatrix[i][j+1] * inflationPercents[j+1]);
        }
    }

    for (int i=0;i<inflationPercents.length();i++)
    {
        for (int j=0;j<inflationPercents.length();j++)
        {
            debugMatrix += QString::number(inflationMatrix[i][j]) + " ";
        }
        debugMatrix += '\n' ;
    }
    qDebug() << debugMatrix;

    for (int i=0;i<okrYears.length();i++)
    {
        if (okrYears[i]>0 || serialYears[i]>0)
        {
            int curYear = i;
            if (okrYears[i]>0)
            {
                if (firstUnit)
                {
                    for (int j=currentProject.getPrePrices().length()-1;j>-1;j--)
                    {
                        if (curYear-difPreFirstUnit>=0 && curYear-difPostLastUnit<okrYears.length())
                            unitPrices[curYear-difPreFirstUnit]+=currentProject.getPrePrices()[j]*inflationMatrix[currentProject.getPrePricesStartYear()-2024][curYear-difPreFirstUnit-j];
                        curYear--;
                    }
                }
                curYear = i;
                if (i == lastUnitYear)
                {
                    for (int j=currentProject.getPostPrices().length()-1;j>-1;j--)
                    {
                        if (curYear-difPostLastUnit>=0 && curYear-difPostLastUnit<okrYears.length())
                            unitPrices[curYear-difPostLastUnit]+=currentProject.getPostPrices()[j]*inflationMatrix[currentProject.getPostPricesStartYear()-currentProject.getPostPrices().length()-2024][curYear-difPostLastUnit-j];
                        curYear--;
                    }
                }
                curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getFirstUnitPrices()[j]*okrYears[i] *inflationMatrix[currentProject.getFirstUnitStartYear()-2024][curYear-j];
                    curYear--;
                }

            }
            if (serialYears[i]>0)
            {
                int curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getSerialPrices()[j]*serialYears[i]*inflationMatrix[currentProject.getSerialPricesStartYear()-2024][curYear-j];
                    curYear--;
                }
            }
            qreal spacecraftWeigth = mainModel->db.getSpacecraftWeightByProjectName(projectName);
            firstUnit = false;
            int fInd;
            int sInd;
            fInd = boosterRocketValues[i].indexOf(" ");
            QString boosterRocketName = boosterRocketValues[i].mid(0,fInd);
            sInd = boosterRocketValues[i].indexOf("(");
            QString upperBlockName = boosterRocketValues[i].mid(fInd+3,sInd-(fInd+4));
            QString spaceportName = boosterRocketValues[i].mid(sInd+1, boosterRocketValues[i].length()-(sInd+2));
            DBlaunch currentLaunch = mainModel->db.getLaunchFromParamIds(boosterRocketName, upperBlockName, spaceportName);
            qreal launchPrice = currentLaunch.launch_price();
            qreal deliveryPrice = currentLaunch.delivery_price();
            int launchDeliveryStartYear = currentLaunch.price_year();
            QPair<QVector<qreal>,int> boosterRocketPricesYear = pricesTextToVector(currentLaunch.prices());
            QVector<qreal> boosterRocketPricestmp = boosterRocketPricesYear.first;
            int boosterRocketStartYear = boosterRocketPricesYear.second;
            curYear = i;
            if (currentLaunch.max_payload() >= spacecraftWeigth){
                boosterRocketPrices[curYear]+=(launchPrice+deliveryPrice)*inflationMatrix[launchDeliveryStartYear -2024][curYear];
                if ((blockValues[i]==0)|| (brChanged && column == i)) blockValues[i] = currentLaunch.max_payload() / spacecraftWeigth;
                for (int j=boosterRocketPricestmp.length()-1;j>-1;j--)
                {
                    if (curYear>=0 && curYear<okrYears.length())
                        boosterRocketPrices[curYear]+=boosterRocketPricestmp[j]*int(((okrYears[i]+serialYears[i])+blockValues[i]-1)/blockValues[i])*inflationMatrix[boosterRocketStartYear-2024][curYear-j];
                    curYear--;
                }

            }
        }
        else
        {
            blockValues[i]=0;
        }
    }


    bool expected = false;
    int expectedYears = -1;
    for (int i=0;i<okrYears.length();i++)
    {
        unitResultValues[i].first = QString::number(okrYears[i]);
        unitResultValues[i].second = "normal";
        serialUnitResultValues[i].first = QString::number(serialYears[i]);
        serialUnitResultValues[i].second = "normal";

        blockResultValues[i].first = QString::number(blockValues[i]);
        blockResultValues[i].second = "normal";
        boosterRocketResultValues[i].first = boosterRocketValues[i];
        boosterRocketResultValues[i].second = "normal";

        unitPricesResultValues[i].first = QString::number(unitPrices[i]);
        unitPricesResultValues[i].second = "number";
        rocketPricesResultValues[i].first = QString::number(boosterRocketPrices[i]);
        rocketPricesResultValues[i].second = "number";
        if (okrYears[i]>0 || serialYears[i]>0)
        {
            if (okrYears[i]>0)
                unitResultValues[i].second = "current";
            if (serialYears[i]>0)
                serialUnitResultValues[i].second = "current";
            expected = true;
            expectedYears = unitLifeTime;
        }
        if (expectedYears == 0)
        {
            expected = false;
            unitResultValues[i].second = "expected";
            serialUnitResultValues[i].second = "expected";
        }
        expectedYears --;
    }

    QVector<QVector<QPair<QString,QString>>> resultVector;
    resultVector.append(unitResultValues);
    resultVector.append(serialUnitResultValues);
    resultVector.append(blockResultValues);
    resultVector.append(boosterRocketResultValues);
    resultVector.append(unitPricesResultValues);
    resultVector.append(rocketPricesResultValues);
    //resultVector.append(unitPrices);
    //qDebug()<<resultVector;
    return resultVector;
}

QPair<QVector<qreal>,int> TabPredictionModel::pricesTextToVector(QString pricesString)
{
    QVector <qreal> pricesVector;
    int pricesStartYear = -1;
    QStringList prices = pricesString.split(";");
    bool foundFirstPrice = false;
    for (int i=0;i<prices.length();i++)
    {
        if(!foundFirstPrice)
        {
            if (prices[i]!="0")
            {
                pricesStartYear = 2024 + i;
                foundFirstPrice = true;
            }
        }
        if (foundFirstPrice)
        {
            pricesVector.append(prices[i].toDouble());
        }
    }
    foundFirstPrice = false;
    for(int i=pricesVector.length()-1;i!=0;i--)
    {
        if (!foundFirstPrice)
        {
            if (pricesVector[i] != 0)
                foundFirstPrice = true;
            else
                pricesVector.removeAt(i);
        }
        if (foundFirstPrice) break;
    }
    return QPair<QVector<qreal>,int>(pricesVector, pricesStartYear);
}

QVector<int> TabPredictionModel::fileRowTextToVector(QString rowString)
{
    QVector <int> rowVector;
    QStringList prices = rowString.split(";");
    for (int i=0;i<prices.length();i++)
    {
        rowVector.append(prices[i].toDouble());
    }

    return rowVector;
}

void TabPredictionModel::saveToFile(QVector<FileProjectValue> saveValues, QString filePath)
{
    QString resultString;
    for (int i=0;i<saveValues.length();i++)
    {
        QVector <QString> launchValueVector = saveValues[i].getLaunchValues();
        QString okrYears = "", serialYears = "", unitBlock = "", launchIds = "";

        for (int j=0;j<launchValueVector.length();j++)
        {
            okrYears += (QString::number(saveValues[i].getOkrYears()[j]) + ";");
            serialYears += (QString::number(saveValues[i].getSerialYears()[j]) + ";");
            unitBlock += (QString::number(saveValues[i].getUnitBlocks()[j]) + ";");

            int fInd;
            int sInd;
            fInd = launchValueVector[j].indexOf(" ");
            QString boosterRocketName = launchValueVector[j].mid(0,fInd);
            sInd = launchValueVector[j].indexOf("(");
            QString upperBlockName = launchValueVector[j].mid(fInd+3,sInd-(fInd+4));
            QString spaceportName = launchValueVector[j].mid(sInd+1, launchValueVector[j].length()-(sInd+2));

            launchIds += (QString::number(mainModel->db.getLaunchFromParamIds(boosterRocketName, upperBlockName, spaceportName).id()) + ";");
        }
        okrYears.remove(okrYears.length()-1,1);
        serialYears.remove(serialYears.length()-1,1);
        unitBlock.remove(unitBlock.length()-1,1);
        launchIds.remove(launchIds.length()-1,1);
        resultString += QString::number(mainModel->db.getProjectInfoFromName(saveValues[i].getProjectName()).id()) + "," + okrYears + "," + serialYears + "," + unitBlock + "," + launchIds + "\n";
    }
    QFile out(filePath);
    if( out.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &out );
        stream << resultString;
        out.close();
    }
//    QFile in( FILE_NAME );
//    if( in.open( QIODevice::ReadOnly ) ) {
//        QTextStream stream( &in );
//        qDebug() << stream.readAll();
//        in.close();
//    }
}
QVector<FileProjectValue> TabPredictionModel::loadFromFile(QString filePath)
{
    QString values;
    QFile in(filePath);
    if( in.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &in );
        values = stream.readAll();
        in.close();
    }
    QVector<FileProjectValue> resultVector;
    QStringList projectValues = values.split("\n");
    projectValues.removeLast();
    for (int i=0;i<projectValues.length();i++)
    {
        QStringList rows = projectValues[i].split(",");
        QString projectName = mainModel->db.getProjectInfoFromId(rows[0].toInt()).name();
        QVector<int> okrYears = fileRowTextToVector(rows[1]);
        QVector<int> serialYears = fileRowTextToVector(rows[2]);
        QVector<int> unitBlocks = fileRowTextToVector(rows[3]);
        QVector<int> launchIds = fileRowTextToVector(rows[4]);
        QVector<QString> launchValues;

        for (int j=0;j<launchIds.length();j++)
        {
            DBlaunch a = mainModel->db.getLaunchById(launchIds[i]);
            QString boosterRocketName = mainModel->db.getNameFromTableById("unit",a.booster_rocket_id());
            QString upperBlockName = mainModel->db.getNameFromTableById("unit",a.upper_block_id());
            QString spaceportName = mainModel->db.getNameFromTableById("spaceport",a.spaceport_id());
            launchValues.append(boosterRocketName + " с " + upperBlockName + " (" + spaceportName+ ")");
        }
        resultVector.append(FileProjectValue(projectName, okrYears, serialYears, unitBlocks, launchValues));
    }
    return resultVector;
}

void TabPredictionModel::projectModelClear()
{
    predictionModel.clear();
}
