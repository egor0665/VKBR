#include "tabpredictionmodel.h"

#include <qstringlist.h>
#include <QDebug>
#include <FileProjectValue.h>
#include <QFile>
#include <QTextDocument>
#include <QTextTableFormat>
#include <QTextCursor>
#include <QTextTableCell>
#include <QTableWidgetItem>
#include <QPrinter>
#include <PALETTE.h>

TabPredictionModel::TabPredictionModel()
{

}

TabPredictionModel::TabPredictionModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

void TabPredictionModel::setUpValues()
{
    QVector<qreal> inflationPercents = mainModel->db.getInflationPercents(2024,2040);
    qDebug() << inflationPercents;

    for (int i=0;i<inflationPercents.length();i++)
    {
        for (int j=i+1;j<inflationPercents.length();j++)
        {
            inflationMatrix[i][j] = 0;
        }
    }
    for (int i=0;i<inflationPercents.length();i++)
            inflationMatrix[i][i] = 1;

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
            inflationMatrix[i][j] = inflationMatrix[i][j+1] * 1/inflationPercents[j+1];
        }
    }

//    for (int i=0;i<inflationPercents.length();i++)
//    {
//        for (int j=0;j<inflationPercents.length();j++)
//        {
//            debugMatrix += QString::number(inflationMatrix[i][j]) + " ";
//        }
//        debugMatrix += '\n' ;
//    }
//    qDebug() << debugMatrix;
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
    int difPreFirstUnit = currentProject.getFirstUnitStartYear() - currentProject.getPrePricesStartYear()-1;
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

    bool serialUnits=false;
    for (int i=0;i<serialYears.length();i++)
        if (serialYears[i]>0)
            serialUnits = true;

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
                            unitPrices[curYear-difPreFirstUnit]+=currentProject.getPrePrices()[j]*inflationMatrix[currentProject.getFirstUnitStartYear()+currentProject.getFirstUnitPrices().length() -1 - 2024][i];
                        curYear--;
                    }
                }
                curYear = i;
                if (i == lastUnitYear && serialUnits)
                {
                    for (int j=currentProject.getPostPrices().length()-1;j>-1;j--)
                    {
                        if (curYear-difPostLastUnit>=0 && curYear-difPostLastUnit<okrYears.length())
                            unitPrices[curYear-difPostLastUnit]+=currentProject.getPostPrices()[j]*inflationMatrix[currentProject.getFirstUnitStartYear()+currentProject.getFirstUnitPrices().length() -1 - 2024][i];
                        curYear--;
                    }
                }
                curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getFirstUnitPrices()[j]*okrYears[i] *inflationMatrix[currentProject.getFirstUnitStartYear()+currentProject.getFirstUnitPrices().length() -1 - 2024][i];
                    curYear--;
                }

            }
            if (serialYears[i]>0)
            {
                int curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getSerialPrices()[j]*serialYears[i]*inflationMatrix[currentProject.getFirstUnitStartYear()+currentProject.getFirstUnitPrices().length() -1 - 2024][i];
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
                boosterRocketPrices[curYear]+=(launchPrice+deliveryPrice)*inflationMatrix[launchDeliveryStartYear -2024][i];
                if ((blockValues[i]==0)|| (brChanged && column == i)) blockValues[i] = currentLaunch.max_payload() / spacecraftWeigth;
                for (int j=boosterRocketPricestmp.length()-1;j>-1;j--)
                {
                    if (curYear>=0 && curYear<okrYears.length())
                        boosterRocketPrices[curYear]+=boosterRocketPricestmp[j]*int(((okrYears[i]+serialYears[i])+blockValues[i]-1)/blockValues[i])*inflationMatrix[boosterRocketStartYear+boosterRocketPricestmp.length() -1 - 2024][i];
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
    fileManager = new FileManager();
    fileManager->saveToFile(filePath, resultString);
    delete fileManager;
}

QVector<FileProjectValue> TabPredictionModel::loadFromFile(QString filePath)
{
    fileManager = new FileManager();
    QString values = fileManager->readFile(filePath);
    delete fileManager;

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

void TabPredictionModel::saveToPdf(QString name, QVector<QVector<QString>> data, QVector<QString> values, QVector<QPair<QVector<QString>,QString>> chartValues, int startYear, int endYear, QString filePath)
{
    QTextBlockFormat centerAlignment, header;
    centerAlignment.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    header.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    header.setLineHeight(100,1);
    header.setHeadingLevel(1);

    QTextCharFormat mainHeaderFormat;
    mainHeaderFormat.setFont(QFont("Times New Roman", 18));

    QTextCharFormat verticalTableHeaderFormat;
    verticalTableHeaderFormat.setFont(QFont("Times New Roman", 8));
    verticalTableHeaderFormat.setFontWeight(QFont::Bold);

    QTextCharFormat verticalTypeTableHeaderFormat;
    verticalTypeTableHeaderFormat.setFont(QFont("Times New Roman", 10));
    verticalTypeTableHeaderFormat.setBackground(LINECOLOR);
    verticalTypeTableHeaderFormat.setFontWeight(QFont::Bold);

    QTextCharFormat projectNameLineFormat;
    projectNameLineFormat.setFont(QFont("Times New Roman", 10));
    projectNameLineFormat.setBackground(PROJECTNAMECOLOR);
    projectNameLineFormat.setFontWeight(QFont::Bold);

    QTextCharFormat tableTextFormat;
    tableTextFormat.setFont(QFont("Times New Roman", 8));

    QTextCharFormat tableUnitFormat;
    tableUnitFormat.setFont(QFont("Times New Roman", 8));
    tableUnitFormat.setBackground(UNITLAUNCHCOLOR);

    QTextCharFormat tableHeaderFormat;
    tableHeaderFormat.setFont(QFont("Times New Roman", 8));
    tableHeaderFormat.setBackground(PDFHEADERCOLOR);

    const int columns = endYear-startYear + 2; // ui->tableWidget_8->columnCount();
    const int rows = data.length();
    QTextDocument doc;
    QTextCursor cursor(&doc);
    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(1);
    tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
    tableFormat.clearColumnWidthConstraints();

    cursor.movePosition(cursor.End);
    cursor.setBlockFormat(header);
    cursor.insertText(name,mainHeaderFormat);

    cursor.movePosition(cursor.NextRow);
    tableFormat.setWidth(950);
    QTextLength verticalHeader = QTextLength(QTextLength::FixedLength,100);
    QTextLength verticalCell = QTextLength(QTextLength::FixedLength,800/columns);
    QVector<QTextLength> lengths;
    lengths.append(verticalHeader);
    for (int i=0;i<columns-1;i++)
        lengths.append(verticalCell);
    tableFormat.setColumnWidthConstraints(lengths);
    QTextTable *textTable = cursor.insertTable(rows + 1, columns, tableFormat);

    for (int i = 0; i < columns; i++) {
        QTextTableCell cell = textTable->cellAt(0, i);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        if (i==0)
            cellCursor.insertText("");
        else
            cellCursor.insertText(QString::number(i+startYear-1));
    }
    bool includeLine = true;
    QVector<QString> linesNames = {"Связь", "ДЗЗ", "ФКИ", "Другое", "Цены КА", "Цены РН", "Итого"};
    QVector<QString> typeNames = {"Связь", "ДЗЗ", "ФКИ", "Другое"};
    QVector<QString> totalNames = {"Цены КА", "Цены РН", "Итого"};
    QVector<QString> unitLines = {"Запуск ОКР аппаратов", "Запуск серийных аппаратов"};
    QVector<QString> rowsNames = {"Запуск ОКР аппаратов", "Запуск серийных аппаратов", "Блок КА", "Ракета-носитель", "Цены КА ОКР+Серия", "Цены РН проекта", "Итого"};
    QVector<int> removeRows;
    for (int i = 0; i < rows; i++) {
        bool includeRow = true;
        if (linesNames.contains(data[i][0]))
        {
            if (!values.contains(data[i][0]))
                includeLine = false;
            else
                includeLine = true;
        }
        if (rowsNames.contains(data[i][0]))
        {
            if (!values.contains(data[i][0]))
                includeRow = false;
        }
        if (includeLine & includeRow)
        {

            for (int j = 0; j < columns; j++)
            {
                QString dataVal = data[i][j];
                QTextCharFormat currentCellFormat;
                if (i+1 < rows && data[i+1][0]=="Запуск ОКР аппаратов")
                    currentCellFormat = projectNameLineFormat;
                else if (typeNames.contains(data[i][0]))
                    currentCellFormat = verticalTypeTableHeaderFormat;
                else if (totalNames.contains(data[i][j]))
                {
                    currentCellFormat = verticalTypeTableHeaderFormat;
                    int intVal = data[i][j].toDouble();
                    if (intVal != 0)
                        dataVal = QString::number(intVal);
                }
                else if (unitLines.contains(data[i][0]) && data[i][j]!="" && j>0)
                    currentCellFormat = tableUnitFormat;
                else
                {
                    if (j==0)
                        currentCellFormat = verticalTableHeaderFormat;
                    else
                    {
                        currentCellFormat = tableTextFormat;
                        int intVal = data[i][j].toDouble();
                        if (intVal != 0)
                            dataVal = QString::number(intVal);
                    }
                }
                QTextTableCell cell = textTable->cellAt(i+1, j);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cell.setFormat(currentCellFormat);
                cellCursor.setBlockFormat(centerAlignment);
                cellCursor.insertText(dataVal);
            }
        }
        else
            removeRows.append(i+1);
    }
    for(int i=rows;i>=0;i--)
    {
        if (removeRows.contains(i))
        {
            textTable->removeRows(i,1);
        }
    }
    //------
    QVector <QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>> prices;
    prices.append(QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>("Итого",QPair<QVector<qreal>,QVector<qreal>>({},{})));
    prices.append(QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>("Связь",QPair<QVector<qreal>,QVector<qreal>>({},{})));
    prices.append(QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>("ДЗЗ",QPair<QVector<qreal>,QVector<qreal>>({},{})));
    prices.append(QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>("ФКИ",QPair<QVector<qreal>,QVector<qreal>>({},{})));
    prices.append(QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>("Другое",QPair<QVector<qreal>,QVector<qreal>>({},{})));
    for (int i=1+startYear-2024;i<endYear-2024+1;i++)
    {
        prices[0].second.first.append(0);
        prices[0].second.second.append(0);
        prices[1].second.first.append(0);
        prices[1].second.second.append(0);
        prices[2].second.first.append(0);
        prices[2].second.second.append(0);
        prices[3].second.first.append(0);
        prices[3].second.second.append(0);
        prices[4].second.first.append(0);
        prices[4].second.second.append(0);
    }
    QVector<QString> rowValuesUnit = {"КА Цены", "Цены КА ОКР+Серия"};
    //QVector<QString> rowValuesBoosterRocket = {"Цены РН проекта", "Цены РН проекта"};
    QVector<QString> spacecraftTypes = {"Связь", "ДЗЗ", "ФКИ", "Другое"};
    QVector<QString> mainRowTypes = {"Связь", "ДЗЗ", "ФКИ", "Другое", "Итого"};
    int currentType = -1;
    int unitNum = 0;
    for (int i=0;i<data.length();i++)
    {
        if (spacecraftTypes.contains(data[i][0]))
            currentType++;
        QString rowName = data[i][0];
        if (rowValuesUnit.contains(rowName))
        {
            QVector<qreal> pricesTmpUnit;
            QVector<qreal> pricesTmpBoosterRocket;
            for (int j=1+startYear-2024;j<endYear-2024+1;j++)
            {
                pricesTmpUnit.append(data[i][j].toDouble());
                pricesTmpBoosterRocket.append(data[i+1][j].toDouble());
                prices[currentType+1+unitNum].second.first[j-1] += data[i][j].toDouble();
                prices[currentType+1+unitNum].second.second[j-1] += data[i+1][j].toDouble();
                prices[0].second.first[j-1] += data[i][j].toDouble();
                prices[0].second.second[j-1] += data[i+1][j].toDouble();
            }
            prices.insert(currentType+1+unitNum,QPair<QString,QPair<QVector<qreal>,QVector<qreal>>>(data[i-5][0],QPair<QVector<qreal>,QVector<qreal>>(pricesTmpUnit, pricesTmpBoosterRocket)));
            unitNum++;
        }
    }

    for (int j=0;j<chartValues.length();j++)
    {
        QChart *chart = new QChart();
        if (chartValues[j].first.contains("Направления"))
        {
            for (int i=0;i<prices.length();i++)
            {
                if (spacecraftTypes.contains(prices[i].first))
                {
                    QLineSeries* series = new QLineSeries();
                    series->setName(prices[i].first);
                    for(int k=0;k<prices[i].second.first.length();k++)
                        series->append(k-1, prices[i].second.first[k]+prices[i].second.second[k]);
                    chart->addSeries(series);
                }
            }
        }
        if (chartValues[j].first.contains("Итого"))
        {
            for (int i=0;i<prices.length();i++)
            {
                if (prices[i].first=="Итого")
                {
                    QLineSeries* series = new QLineSeries();
                    series->setName(prices[i].first);
                    for(int k=0;k<prices[i].second.first.length();k++)
                        series->append(k-1, prices[i].second.first[k]+prices[i].second.second[k]);
                    chart->addSeries(series);
                }
            }
        }
        int lastType = 1;
        for (int i=0;i<prices.length();i++)
        {
            if (((chartValues[j].first.contains("КА Связь") && lastType==1) ||
                    (chartValues[j].first.contains("КА ДЗЗ") && lastType==2) ||
                    (chartValues[j].first.contains("КА ФКИ") && lastType==3) ||
                    (chartValues[j].first.contains("КА Другое") && lastType==4)) && prices[i].first != "Итого" && !spacecraftTypes.contains(prices[i].first))
            {
                QLineSeries* series = new QLineSeries();
                series->setName(prices[i].first);
                for(int k=0;k<prices[i].second.first.length();k++)
                    series->append(k-1, prices[i].second.first[k]+prices[i].second.second[k]);
                chart->addSeries(series);
            }
            if (spacecraftTypes.contains(prices[i].first))
                lastType ++;
        }
        QValueAxis * axisX = new QValueAxis();
        axisX->setRange(startYear-2000,endYear-2000-1);
        axisX->setTickCount(endYear-startYear);
        axisX->setTickInterval(1);
        axisX->setTickAnchor(24);
        axisX->setTickType(QValueAxis::TicksDynamic);
        axisX->setTitleText("Год 2000+");
//        QValueAxis * axisY = new QValueAxis();
//        axisY->setTitleText("Цены");
        chart->createDefaultAxes();
        chart->setAxisX(axisX);
        chart->setTitle("Цена - Год");

        chart->legend()->setAlignment(Qt::AlignRight);
        QPalette a;
        QChartView* tmpChartView = new QChartView();
        tmpChartView->setChart(chart);
        tmpChartView->resize(1000,595);
        QPixmap p = tmpChartView->grab();
        QImage img = p.toImage();
        img = img.scaled(1000,595);

        cursor.movePosition(cursor.End);
        cursor.movePosition(cursor.NextRow);
        cursor.insertImage(img);
    }

    doc.setDocumentMargin(0);
    doc.setTextWidth(4);
    fileManager = new FileManager();
    fileManager->printPDF(&doc, filePath);
    delete fileManager;
}
