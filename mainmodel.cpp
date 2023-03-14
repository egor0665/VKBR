#include "DBspacecraft.h"
#include "mainmodel.h"
#include <QVariant>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <dbChangeValue.h>
#include <DBunit.h>
#include <DBProject.h>
#include <projectset.h>
#include <DBlaunch.h>

MainModel::MainModel()
{
    db = database();
    db.createConnection();
}

void MainModel::createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot)
{
    navigatiorMenuRoot->setText(0, "Каталог");
    QVector <QPair<QString,QString>> units = db.getUnitClassesAndNames();
    qDebug() << units;
    QString lastclass = "";
    QVector <QString> nameArray;

    for (int i=0;i < units.size();i++){
        QString _class = units[i].first;
        QString _name = units[i].second;

        if (lastclass!=_class){
            if (!nameArray.empty()){
                addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
            }
            nameArray.clear();
            lastclass = _class;
        }
        nameArray.append(_name);

    }
    addTreeChild(navigatiorMenuRoot, classSelect(lastclass), nameArray);
    return;
}

void MainModel::addTreeChild(QTreeWidgetItem *parent,
                              QString name, QVector <QString> child_array)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    for (int i=0; i<child_array.size();i++){
        addTreeChild2(treeItem, child_array[i]);
    }

}
void MainModel::addTreeChild2(QTreeWidgetItem *parent,
                               QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
}

QString MainModel::classSelect(QString _class)
{
    qDebug() << _class;
    QString resultClass;
    if (_class == "РН")
        resultClass = "Ракеты-носители";
    else if (_class == "РБ")
        resultClass = "Разгонные блоки";
    else if (_class == "ПГК")
        resultClass = "Пилотируемые и грузовые космические корабли/аппара";
    else if (_class == "КАС")
        resultClass = "Космические аппараты связи, вещания и ретрансляции, поиска и спасения";
    else
        resultClass = _class;
    qDebug() << _class << resultClass << endl;
    return resultClass;
}

QVector<QPair<QString,QString>> MainModel::getUnitData(int unitId)
{
    QVector<QPair<QString,QString>> result = vectorUnitData(unitId);
    QString unitClass = db.getUnitClassById(unitId);
    if (unitClass == "РН")
        result.append(vectorBoosterRocketData(unitId));
    else if (unitClass == "РБ")
        result.append(vectorUpperBlockData(unitId));

    qDebug() << result;
    return result;
}
//QVector<QPair<QString,QStringList>> getUnitEconDataById(int unitId)
//{
//    return splitValues(db.getUnitEconDataById(unitId));
//}

int MainModel::getUnitIdByName(QString unitName)
{
    return db.getUnitIdByName(unitName);
}

QVector<QPair<QString,QString>> MainModel::vectorUnitData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBUnit selectedUnit = db.getUnitInfoFromId(unitId);

    QStringList values = selectedUnit.getValues();
    for (int i=0;i<selectedUnit.UNIT_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUnit.UNIT_VALUES[i] == "Разработчик" || selectedUnit.UNIT_VALUES[i] == "Разработчик 2" || selectedUnit.UNIT_VALUES[i] == "Производитель" || selectedUnit.UNIT_VALUES[i] == "Заказчик")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getOrganizationInfoFromId(values[i].toInt()).name()));
            else if (selectedUnit.UNIT_VALUES[i] == "Космодром первого запуска")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db.getSpaceportInfoFromId(values[i].toInt()).name()));
            else
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QPair<QString,QString>> MainModel::vectorBoosterRocketData(int boosterRocketId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBBooster_rocket selectedBooster_rocket = db.getBooster_rocketInfoFromId(boosterRocketId);
    QStringList values = selectedBooster_rocket.getValues();
    for (int i=0;i<selectedBooster_rocket.BOOSTER_ROCKET_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="phys_info" || selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="econ_info")
                vectoredData.append(splitValues(values[i]));
            else
                vectoredData.append(QPair<QString,QString>(selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector <QPair<QString,QString>> MainModel::vectorUpperBlockData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBUpper_block selectedUpper_block = db.getUpper_blockInfoFromId(unitId);
    QStringList values = selectedUpper_block.getValues();
    for (int i=0;i<selectedUpper_block.UPPER_BLOCK_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUpper_block.UPPER_BLOCK_VALUES[i]=="phys_info" || selectedUpper_block.UPPER_BLOCK_VALUES[i]=="econ_info")
                vectoredData.append(splitValues(values[i]));
            else
                vectoredData.append(QPair<QString,QString>(selectedUpper_block.UPPER_BLOCK_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QPair<QString,QString>> MainModel::splitValues(QString values)
{
    qDebug()<<"splitvalues" + values;
    QVector<QPair<QString,QString>> resultValues;
    QStringList stringVals = values.split("\n");
    for (int j=0;j<stringVals.length();j++){
        QStringList pair = stringVals[j].split("==");
        resultValues.append(QPair<QString,QString>(pair[0], pair[1]));
    }
    return resultValues;
}

QVector<QPair<QString,QStringList>> MainModel::formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2)
{
    QVector<QPair<QString,QStringList>> compareVector;
    QVector<QPair<QString,QStringList>> singleValuesVector;
    for (int i=0; i<unitValues_1.length();i++)
    {
        QString compVal = unitValues_1[i].first;
        bool found = false;
        for (int j=0;j<unitValues_2.length();j++)
        {
            if (unitValues_2[j].first==compVal){
                compareVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second,unitValues_2[j].second}));
                found=true;
                break;
            }
        }
        if (!found) {
            singleValuesVector.append(QPair<QString,QStringList>(compVal, {unitValues_1[i].second, ""}));
        }
    }

    for (int i=0; i<unitValues_2.length();i++)
    {
        QString compVal = unitValues_2[i].first;
        bool found = false;
        for (int j=0;j<unitValues_1.length();j++)
        {
            if (unitValues_1[j].first==compVal){
                found=true;
                break;
            }
        }
        if (!found) {
            singleValuesVector.append(QPair<QString,QStringList>(compVal, { "", unitValues_2[i].second}));
        }
    }
    compareVector.append(singleValuesVector);
    return compareVector;
}

qreal MainModel::getNumberFromString(QString line, int param)
{
    //param
    // 0 - first
    // 1 - min
    // 2 - max
    // 3 - last
    qreal first,min,max,last,cur,divider;
    int i=0;
    bool firstNum = true;
    while (i<= line.length())
    {
        cur = 0;
        divider = 1;
        bool gotDivider=false;
        bool gotNum = false;
        while (line[i].isDigit() || line[i]=="." || line[i]==",")
        {
            if (gotDivider)
                divider /= 10;
            if (line[i].isDigit())
                cur=cur*10+line[i].digitValue();
            else
                gotDivider = true;
            i++;
            gotNum = true;
        }
        if (gotNum)
        {
            cur *= divider;
            if (firstNum) {
                min = cur;
                max = cur;
                first = cur;
                firstNum = false;
            }
            if (cur<min) min = cur;
            if (cur>max) max = cur;
            last = cur;
            qDebug() << cur << last << first << min << max;
        }
        i++;
    }
    if (firstNum)
    {
        first = 0;
        min = 0;
        max = 0;
        last = 0;
        cur = 0;
    }
    switch (param) {
    case 0:
        return first;
    case 1:
        return min;
    case 2:
        return max;
    case 3:
        return last;
    default:
        return first;
    }
}

QStringList MainModel::getNamesFromTableStringList(QString tableName)
{
     return QVectorToQStringList(getNamesFromTable(tableName));
}

QVector<QString> MainModel::getNamesFromTable(QString tableName)
{
    return db.getNamesFromTable(tableName);
}

QStringList MainModel::getTableDescriptionsStringList()
{
    return QVectorToQStringList(getTableDescriptions());
}
QVector <QString> MainModel::getTableDescriptions()
{
    return db.getTableDescriptions();
}

QStringList MainModel::QVectorToQStringList(QVector<QString> vector)
{
    QStringList result = {};
    for (int i=0;i<vector.length();i++)
    {
        result.append(vector[i]);
    }
    return result;
}

int MainModel::getTableColumnCount(QString tableName)
{
    return db.getTableColumnCount(tableName);
}

QVector <QString> MainModel::getTableColumnNames(QString tableName)
{
    return db.getTableColumnNames(tableName);
}

QStringList MainModel::getTableColumnNamesStringList(QString tableName)
{
    return QVectorToQStringList(getTableColumnNames(tableName));
}

QString MainModel::getUnitImageFromId(int unitId)
{
    return db.getUnitImageFromId(unitId);
}

QVector <QVector<QString>> MainModel::getValuesFromTable(QString tableName, int valuesNum)
{
    return db.getValuesFromTable(tableName, valuesNum);
}

QString MainModel::updateDataInTable(QString tableName, QVector<dbChangeValue> dbValuesToChange)
{
    return db.updateDataInTable(tableName, dbValuesToChange);
}

QString MainModel::addUnitToDB(QString unit_class,
                               QString name,
                               QString purpose,
                               QString project,
                               QString objective,
                               QString work_status,
                               QString developer,
                               QString extra_developer,
                               QString manufacturer,
                               int launches,
                               QString customer,
                               int successful,
                               QDateTime first_launch,
                               QString first_launch_spaceport,
                               QString financing_type,
                               QString control_system_type,
                               QString image_url,
                               qreal price,
                               int price_year,
                               qreal maxPayload,
                               qreal minPayload,
                               qreal weight,
                               QString physInfo,
                               QString econInfo
                               )
{
    bool proj;
    if (project == "Да") proj = true;
    else proj = false;
    int devId = db.getOrganizationIdFromName(developer);
    int extrDevId = db.getOrganizationIdFromName(extra_developer);
    int manId = db.getOrganizationIdFromName(manufacturer);
    int custId = db.getOrganizationIdFromName(customer);
    int spaceportId = db.getSpaceportIdFromName(first_launch_spaceport);
    DBUnit newUnit = DBUnit(-1,unit_class,name,purpose,
                            proj,objective,work_status,
                            devId,extrDevId,manId,launches,
                            custId,successful,first_launch,
                            spaceportId,financing_type,
                            control_system_type,image_url,
                            price,price_year);
    int newUnitId = db.addUnitToDBRetId(newUnit);

    if (unit_class == "РН")
    {
        DBBooster_rocket newBoosterRocket = DBBooster_rocket(newUnitId, maxPayload, minPayload, physInfo, econInfo);
        db.addBoosterRocketToDB(newBoosterRocket);
        int boosterRocketId = db.getUnitIdByName(name);
        QVector<int> upperBlockIds = db.getIdsFromTable("upper_block");
        QVector<int> spaceportIds = db.getIdsFromTable("spaceport");
        for (int i=0;i<upperBlockIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketId, upperBlockIds[i],spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0);
                db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "РБ")
    {
        DBUpper_block newUpperBlock = DBUpper_block(newUnitId, physInfo, econInfo);
        db.addUpperBlockToDB(newUpperBlock);
        int upperBlockId = db.getUnitIdByName(name);
        QVector<int> boosterRocketIds = db.getIdsFromTable("booster_rocket");
        QVector<int> spaceportIds = db.getIdsFromTable("spaceport");
        for (int i=0;i<boosterRocketIds.length();i++)
            for (int j=0;j<spaceportIds.length();j++)
            {
                DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketIds[i], upperBlockId,spaceportIds[j],2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0);
                db.addLaunchInformation(tmpLaunch);
            }
    }
    else if (unit_class == "ПТК")
    {

    }
    else if (unit_class == "КА")
    {
        DBSpacecraft newSpacecraft = DBSpacecraft(newUnitId, weight, physInfo, econInfo);
        db.addSpacecraftToDB(newSpacecraft);
    }
    return "db.addUnitToDBRetId(newUnit);";
}

void MainModel::addOrganizationToDB(QString name)
{
    DBOrganization newOrganization = DBOrganization(-1, name);
    db.addOrganoizationToDB(newOrganization);
}

void MainModel::addSpaceportToDB(QString name)
{
    DBSpaceport newSpaceport = DBSpaceport(-1, name);
    db.addSpaceportToDB(newSpaceport);

    int spaceportId = db.getSpaceportIdFromName(name);
    QVector<int> boosterRocketIds = db.getIdsFromTable("booster_rocket");
    QVector<int> upperBlockIds = db.getIdsFromTable("upper_block");
    for (int i=0;i<boosterRocketIds.length();i++)
        for (int j=0;j<upperBlockIds.length();j++)
        {
            DBlaunch tmpLaunch = DBlaunch(-1, boosterRocketIds[i], upperBlockIds[j],spaceportId,2020,"0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",0,0,0,0);
            db.addLaunchInformation(tmpLaunch);
        }
}

void MainModel::addProjectToDB(QString name, QString type, QString unit_name)
{
    int unit_id = db.getUnitIdByName(unit_name);
    DBProject newProject = DBProject(-1, name, type, unit_id, "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;",
                                     "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;");
    db.addProjectToDB(newProject);
}

QVector<QVector<qreal>> MainModel::getProjectPricesFromName(QString projectName)
{
    DBProject currentProject = db.getProjectInfoFromName(projectName);
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

void MainModel::updateProjectInfo(QString projectName, QVector<qreal> pre_prices, QVector<qreal> first_unit_prices, QVector<qreal> last_unit_prices, QVector<qreal> post_prices, QVector<qreal> serial_prices)
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
    db.updateProjectPricesByName(projectName,new_pre_prices,new_first_unit_prices, new_last_unit_prices, new_post_prices,new_serial_prices);
}
QPair<QVector<qreal>,int> MainModel::pricesTextToVector(QString pricesString)
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
int MainModel::projectModelAddProject(QString projectName)
{
    DBProject project = db.getProjectInfoFromName(projectName);
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
        projectLifetime = db.getSpacecraftLifetimeById(project.unit_id());
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

void MainModel::projectModelRemoveProject(QString projectName)
{
    predictionModel.removeProject(projectName);
}

int MainModel::projectModelGetProjectNumber(QString projectName)
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

QStringList MainModel::getUnitNamesByTypeStringList(QString type)
{
    return QVectorToQStringList(db.getUnitNamesByType(type));
}

DBlaunch MainModel::getLaunchFromParamIds(QString boosterRocket, QString upperBlock, QString spaceport)
{
    return db.getLaunchFromParamIds(boosterRocket, upperBlock, spaceport);
}

QVector<qreal> MainModel::pricesToVector(QString prices)
{
    QVector<qreal> pricesVector;
    QStringList vals = prices.split(";");
    for (int i=0;i<vals.length();i++)
        pricesVector.append(vals[i].trimmed().toDouble());
    qDebug()<<pricesVector;
    return pricesVector;
}

QVector<QVector<QPair<QString,QString>>> MainModel::predictPrices(QString projectName, QVector<QVector<int>> yearsValues, QVector<QString> boosterRocketValues, bool brChanged, int column)
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
                            unitPrices[curYear-difPreFirstUnit]+=currentProject.getPrePrices()[j];
                        curYear--;
                    }
                }
                curYear = i;
                if (i == lastUnitYear)
                {
                    for (int j=currentProject.getPostPrices().length()-1;j>-1;j--)
                    {
                        if (curYear-difPostLastUnit>=0 && curYear-difPostLastUnit<okrYears.length())
                            unitPrices[curYear-difPostLastUnit]+=currentProject.getPostPrices()[j];
                        curYear--;
                    }
                }
                curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getFirstUnitPrices()[j]*okrYears[i];
                    curYear--;
                }

            }
            if (serialYears[i]>0)
            {
                int curYear = i;
                for (int j=currentProject.getFirstUnitPrices().length()-1;j>-1;j--)
                {
                    if (curYear>=0&& curYear<okrYears.length())
                        unitPrices[curYear]+=currentProject.getSerialPrices()[j]*serialYears[i];
                    curYear--;
                }
            }
            qreal spacecraftWeigth = db.getSpacecraftWeightByProjectName(projectName);
            firstUnit = false;
            int fInd;
            int sInd;
            fInd = boosterRocketValues[i].indexOf(" ");
            QString boosterRocketName = boosterRocketValues[i].mid(0,fInd);
            sInd = boosterRocketValues[i].indexOf("(");
            QString upperBlockName = boosterRocketValues[i].mid(fInd+3,sInd-(fInd+4));
            QString spaceportName = boosterRocketValues[i].mid(sInd+1, boosterRocketValues[i].length()-(sInd+2));
            DBlaunch currentLaunch = db.getLaunchFromParamIds(boosterRocketName, upperBlockName, spaceportName);
            QPair<QVector<qreal>,int> boosterRocketPricesYear = pricesTextToVector(currentLaunch.prices());
            QVector<qreal> boosterRocketPricestmp = boosterRocketPricesYear.first;
            int boosterRocketStartYear = boosterRocketPricesYear.second;
            curYear = i;
            if (currentLaunch.max_payload() >= spacecraftWeigth){
                if ((blockValues[i]==0)|| (brChanged && column == i)) blockValues[i] = currentLaunch.max_payload() / spacecraftWeigth;
                for (int j=boosterRocketPricestmp.length()-1;j>-1;j--)
                {
                    if (curYear>=0 && curYear<okrYears.length())
                        boosterRocketPrices[curYear]+=boosterRocketPricestmp[j]*int(((okrYears[i]+serialYears[i])+blockValues[i]-1)/blockValues[i]);
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

int MainModel::projectModelGetUnitLifetime(QString projectName)
{
    return predictionModel.getUnitLifetime(projectName);
}

void MainModel::updateLaunchPricesByIds(QString boosterRocketName, QString upperBlockName, QString spaceportName, int priceYear, QString prices, qreal launchPrice, qreal deliveryPrice, qreal minPayload, qreal maxPayload)
{
    int boosterRocketId = db.getUnitIdByName(boosterRocketName);
    int upperBlockId = db.getUnitIdByName(upperBlockName);
    int spaceportId = db.getSpaceportIdFromName(spaceportName);
    db.updateLaunchPricesByIds(boosterRocketId, upperBlockId, spaceportId,priceYear, prices, launchPrice, deliveryPrice, minPayload, maxPayload);
}

QStringList MainModel::getValidLaunchesNamesStringList()
{
    QVector<QVector<int>> ids = db.getValidLaunchesIds();
    QVector<QString> names;
    for (int i=0;i<ids.length();i++)
    {
        QString boosterRocketName = db.getNameFromTableById("unit",ids[i][0]);
        QString upperBlockName = db.getNameFromTableById("unit",ids[i][1]);
        QString spaceportName = db.getNameFromTableById("spaceport",ids[i][2]);
        names.append(boosterRocketName + " с " + upperBlockName + " (" + spaceportName+ ")");
    }

    return QVectorToQStringList(names);
}
