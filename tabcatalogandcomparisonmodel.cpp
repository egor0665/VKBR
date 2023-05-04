#include "tabcatalogandcomparisonmodel.h"
#include <QDebug>
#include <QVector>

TabCatalogAndComparisonModel::TabCatalogAndComparisonModel()
{

}

TabCatalogAndComparisonModel::TabCatalogAndComparisonModel(DataBase *db)
{
    this->db = db;
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::splitValues(QString values)
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

QString TabCatalogAndComparisonModel::getUnitImageFromId(int unitId)
{
    return db->getUnitImageFromId(unitId);
}

QVector<QVector<QPair<QString,QString>>> TabCatalogAndComparisonModel::getUnitData(int unitId)
{
    QVector<QVector<QPair<QString,QString>>> result;
    result.append(vectorUnitData(unitId));
    result.append(QVector<QPair<QString,QString>>());
    result.append(QVector<QPair<QString,QString>>());
    QString unitClass = db->getUnitClassById(unitId);
    if (unitClass == "РН")
    {
        QVector<QVector<QPair<QString,QString>>> tmpValues = vectorBoosterRocketData(unitId);
        result[0].append(tmpValues[0]);
        result[1].append(tmpValues[1]);
        result[2].append(tmpValues[2]);
    }
    else if (unitClass == "РБ")
    {
        QVector<QVector<QPair<QString,QString>>> tmpValues = vectorUpperBlockData(unitId);
        result[0].append(tmpValues[0]);
        result[1].append(tmpValues[1]);
        result[2].append(tmpValues[2]);
    }
    else if (unitClass == "КА")
    {
        QVector<QVector<QPair<QString,QString>>> tmpValues = vectorSpacecraftData(unitId);
        result[0].append(tmpValues[0]);
        result[1].append(tmpValues[1]);
        result[2].append(tmpValues[2]);
    }

    qDebug() << result;
    return result;
}

int TabCatalogAndComparisonModel::getUnitIdByName(QString unitName)
{
    return  db->getUnitIdByName(unitName);
}

QVector<QPair<QString,QString>> TabCatalogAndComparisonModel::vectorUnitData(int unitId)
{
    QVector<QPair<QString,QString>> vectoredData;
    DBUnit selectedUnit = db->getUnitInfoFromId(unitId);

    QStringList values = selectedUnit.getValues();
    for (int i=0;i<selectedUnit.UNIT_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUnit.UNIT_VALUES[i] == "Разработчик" || selectedUnit.UNIT_VALUES[i] == "Разработчик 2" || selectedUnit.UNIT_VALUES[i] == "Производитель" || selectedUnit.UNIT_VALUES[i] == "Заказчик")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db->getOrganizationInfoFromId(values[i].toInt()).name()));
            else if (selectedUnit.UNIT_VALUES[i] == "Космодром первого запуска")
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], db->getSpaceportInfoFromId(values[i].toInt()).name()));
            else
                vectoredData.append(QPair<QString,QString>(selectedUnit.UNIT_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QVector<QPair<QString,QString>>> TabCatalogAndComparisonModel::vectorBoosterRocketData(int boosterRocketId)
{
    QVector<QVector<QPair<QString,QString>>> vectoredData;
    for(int i=0;i<3;i++)
        vectoredData.append(QVector<QPair<QString,QString>>());
    DBBooster_rocket selectedBooster_rocket = db->getBooster_rocketInfoFromId(boosterRocketId);
    QStringList values = selectedBooster_rocket.getValues();
    for (int i=0;i<selectedBooster_rocket.BOOSTER_ROCKET_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="phys_info")
                vectoredData[1].append(splitValues(values[i]));
            else if (selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i]=="econ_info")
                vectoredData[2].append(splitValues(values[i]));
            else
                vectoredData[0].append(QPair<QString,QString>(selectedBooster_rocket.BOOSTER_ROCKET_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QVector <QPair<QString,QString>>> TabCatalogAndComparisonModel::vectorUpperBlockData(int unitId)
{
    QVector<QVector<QPair<QString,QString>>> vectoredData;
    for(int i=0;i<3;i++)
        vectoredData.append(QVector<QPair<QString,QString>>());
    DBUpper_block selectedUpper_block =  db->getUpper_blockInfoFromId(unitId);
    QStringList values = selectedUpper_block.getValues();
    for (int i=0;i<selectedUpper_block.UPPER_BLOCK_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedUpper_block.UPPER_BLOCK_VALUES[i]=="phys_info")
                vectoredData[1].append(splitValues(values[i]));
            else if (selectedUpper_block.UPPER_BLOCK_VALUES[i]=="econ_info")
                vectoredData[2].append(splitValues(values[i]));
            else
                vectoredData[0].append(QPair<QString,QString>(selectedUpper_block.UPPER_BLOCK_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

QVector<QVector <QPair<QString,QString>>> TabCatalogAndComparisonModel::vectorSpacecraftData(int unitId)
{
    QVector<QVector<QPair<QString,QString>>> vectoredData;
    for(int i=0;i<3;i++)
        vectoredData.append(QVector<QPair<QString,QString>>());
    DBSpacecraft selectedSpacecraft =  db->getSpacecraftInfoFromId(unitId);
    QStringList values = selectedSpacecraft.getValues();
    for (int i=0;i<selectedSpacecraft.SPACECRAFT_DEF_ROW_NUM; i++){
        if (values[i]!="" && values[i]!="0"){
            if (selectedSpacecraft.SPACECRAFT_VALUES[i]=="phys_info")
                vectoredData[1].append(splitValues(values[i]));
            else if (selectedSpacecraft.SPACECRAFT_VALUES[i]=="econ_info")
                vectoredData[2].append(splitValues(values[i]));
            else
                vectoredData[0].append(QPair<QString,QString>(selectedSpacecraft.SPACECRAFT_VALUES[i], values[i]));
        }
    }
    return vectoredData;
}

void TabCatalogAndComparisonModel::createNavigationTree(QTreeWidgetItem *navigatiorMenuRoot)
{
    navigatiorMenuRoot->setText(0, "Каталог");

    QVector <QPair<QString,QString>> units = db->getUnitClassesAndNames();
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
    navigatiorMenuRoot->setExpanded(true);
    return;
}

void TabCatalogAndComparisonModel::addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    for (int i=0; i<child_array.size();i++){
        addTreeChild2(treeItem, child_array[i]);
    }
    treeItem->setExpanded(true);
}

void TabCatalogAndComparisonModel::addTreeChild2(QTreeWidgetItem *parent,
                                                 QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
}

QString TabCatalogAndComparisonModel::classSelect(QString _class)
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

QVector<QPair<QString,QStringList>> TabCatalogAndComparisonModel::formCompareTable(QVector<QVector<QPair<QString,QString>>> gotValues)
{
    QVector<QVector<QPair<QString,QString>>> values;
    for (int i=0;i<gotValues.length();i+=3)
    {
        values.append(QVector<QPair<QString,QString>>());
        values[i/3].append(gotValues[i]);
        values[i/3].append(gotValues[i+1]);
        values[i/3].append(gotValues[i+2]);
    }
    QMap<QString,bool> usedValues;
    QVector<QPair<QString,QStringList>> compareVector;
    for (int i=0;i<values.length();i++)
    {
        for (int j=0;j<values[i].length();j++)
        {
            usedValues[values[i][j].first] = false;
        }
    }

    for (int i=0;i<values.length();i++)
    {
        for (int j=0;j<values[i].length();j++)
        {
            QStringList currentValues = {};
            if (!usedValues[values[i][j].first])
            {
                for (int k=0;k<values.length();k++)
                {
                    bool foundValuesInUnit = false;
                    for (int y=0;y<values[k].length();y++)
                    {
                        if (values[k][y].first == values[i][j].first)
                        {
                            foundValuesInUnit = true;
                            currentValues.append(values[k][y].second);
                        }
                    }
                    if (!foundValuesInUnit)
                        currentValues.append("");
                }
                usedValues[values[i][j].first] = true;
                compareVector.append(QPair<QString,QStringList>(values[i][j].first,currentValues));
            }
        }
    }
    return compareVector;
}

QVector <QLineSeries*> TabCatalogAndComparisonModel::createChartLineSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
{
    QVector <QLineSeries*> seriesSummary;
    int compNum = compareValues.length();
    for (int i=0;i<unitNum;i++){
        QLineSeries *series = new QLineSeries();
        series->setName(unitNames[i]);
        for (int j=0;j<compNum;j++){
            series->append(j, compareValues[j]._values[i]);
            qDebug() << j<< compareValues[j]._values[i];
        }
        //series->append(compNum+1, compareValues[0]._values[i]);
        qDebug() << 0 << compareValues[0]._values[i];
        seriesSummary.append(series);
    }

    return seriesSummary;
}

QBarSeries* TabCatalogAndComparisonModel::createChartBarSeries(int unitNum, QVector<CompareValue> compareValues, QStringList unitNames)
{
    QBarSeries* seriesSummary = new QBarSeries;
    int compNum = compareValues.length();
    for (int i=0;i<unitNum;i++){
        QBarSet *set = new QBarSet(unitNames[i]);
        for (int j=0;j<compNum;j++){
            *set <<compareValues[j]._values[i];
            qDebug() << compareValues[j]._values[i];
        }
        seriesSummary->append(set);
        qDebug() << 0 << compareValues[0]._values[i];
    }

    return seriesSummary;
}

void TabCatalogAndComparisonModel::saveToPdfCatalogTab(QString name, QImage image, QVector<QPair<QString, QString>> values, QVector<QPair<QString, QString>> physValues, QVector<QPair<QString, QString>> econValues, QString filePath)
{
    QTextBlockFormat centerAlignment, header;
    centerAlignment.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    header.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    header.setLineHeight(100,1);
    header.setHeadingLevel(1);

    QTextCharFormat textFormat;
    textFormat.setFont(QFont("Times New Roman", 12));
    QTextCharFormat headerFormat;
    headerFormat.setFont(QFont("Times New Roman", 14));
    headerFormat.setFontWeight(QFont::Bold);
    QTextCharFormat mainHeaderFormat;
    mainHeaderFormat.setFont(QFont("Times New Roman", 24));
    mainHeaderFormat.setFontWeight(QFont::Bold);

    int columns = 2;
    int rows = values.length();
    QTextDocument doc;
    QTextCursor cursor(&doc);
    QTextTableFormat tableFormat;

    tableFormat.setHeaderRowCount(1);
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setCellPadding(3);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(0);
    tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
    tableFormat.clearColumnWidthConstraints();

    tableFormat.setWidth(950);
    tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::FixedLength,300),QTextLength(QTextLength::FixedLength,650)});

    cursor.movePosition(cursor.End);

    cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
    cursor.movePosition(cursor.End);

    cursor.setBlockFormat(header);
    cursor.insertText(name, mainHeaderFormat);

    cursor.movePosition(cursor.End);
    QTextTable *mainTable = cursor.insertTable(1, 2, tableFormat);

    QTextTableCell mainTableCell = mainTable->cellAt(0, 0);
    QTextCursor mainTableCellCursor = mainTableCell.firstCursorPosition();
    mainTableCellCursor.insertImage(image);

    tableFormat.setBorder(0.2);
    tableFormat.setWidth(650);
    tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::FixedLength,200),QTextLength(QTextLength::FixedLength,450)});

    mainTableCell = mainTable->cellAt(0, 1);
    mainTableCellCursor = mainTableCell.firstCursorPosition();
    mainTableCellCursor.setBlockFormat(header);
    mainTableCellCursor.insertText("Основные тактико-технические показатели",headerFormat);

    QTextTable *textTable = mainTableCellCursor.insertTable(rows, columns, tableFormat);
    QTextCharFormat tableHeaderFormat;

    for (int i=0;i<rows;i++)
    {
        QTextTableCell cell = textTable->cellAt(i, 0);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(values[i].first,textFormat);
        cell = textTable->cellAt(i, 1);
        cell.setFormat(tableHeaderFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(values[i].second,textFormat);
    }

    tableFormat.setWidth(960);
    tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::FixedLength,300),QTextLength(QTextLength::FixedLength,660)});
    rows = econValues.length();
    cursor.movePosition(cursor.End);
    cursor.setBlockFormat(header);
    cursor.insertText("Основные экономические показатели",headerFormat);
    QTextTable *econTable = cursor.insertTable(rows, columns, tableFormat);
    for (int i=0;i<rows;i++)
    {
        QTextTableCell cell = econTable->cellAt(i, 0);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(econValues[i].first,textFormat);
        cell = econTable->cellAt(i, 1);
        cell.setFormat(tableHeaderFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(econValues[i].second,textFormat);
    }

    rows = econValues.length();
    cursor.movePosition(cursor.End);
    cursor.setBlockFormat(header);
    cursor.insertText("Основные физические показатели",headerFormat);
    QTextTable * physTable = cursor.insertTable(rows, columns, tableFormat);
    for (int i=0;i<rows;i++)
    {
        QTextTableCell cell = physTable->cellAt(i, 0);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(physValues[i].first,textFormat);
        cell = physTable->cellAt(i, 1);
        cell.setFormat(tableHeaderFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerAlignment);
        cellCursor.insertText(physValues[i].second,textFormat);
    }

    doc.setDocumentMargin(0);
    doc.setTextWidth(4);
    fileManager = new FileManager();
    fileManager->printPDF(&doc, filePath);
    delete fileManager;
}

void TabCatalogAndComparisonModel::saveToPdfComparisonTab(QVector<QString> names, QVector<QImage> images, QVector<QVector<QString>> values, QVector<QVector<QString>> compareValues, QVector<int> selectedValues1, QVector<int> selectedValues2, QChartView* chart1 , QChartView* chart2 ,QString filePath)
{
    QTextBlockFormat centerAlignment, header;
    centerAlignment.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    header.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    header.setLineHeight(150,1);
    header.setHeadingLevel(1);

    QTextCharFormat textFormat;
    textFormat.setFont(QFont("Times New Roman", 12));
    QTextCharFormat headerFormat;
    headerFormat.setFont(QFont("Times New Roman", 14));
    headerFormat.setFontWeight(QFont::Bold);
    QTextCharFormat mainHeaderFormat;
    mainHeaderFormat.setFont(QFont("Times New Roman", 24));
    mainHeaderFormat.setFontWeight(QFont::Bold);
    QTextCharFormat secondaryHeaderFormat;
    secondaryHeaderFormat.setFont(QFont("Times New Roman", 14));
    secondaryHeaderFormat.setFontWeight(QFont::Bold);

    int columns = values[0].length();
    int rows = values.length();
    QTextDocument doc;
    QTextCursor cursor(&doc);
    QTextTableFormat tableFormat;

    cursor.movePosition(cursor.NextRow);


    tableFormat.setHeaderRowCount(1);
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setCellPadding(3);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(1);
    tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
    tableFormat.clearColumnWidthConstraints();
    tableFormat.setWidth(950);
    QTextLength verticalHeader = QTextLength(QTextLength::FixedLength,150);
    QTextLength verticalCell = QTextLength(QTextLength::FixedLength,800/columns);
    QVector<QTextLength> lengths;
    lengths.append(verticalHeader);
    for (int i=0;i<columns-1;i++)
        lengths.append(verticalCell);
    tableFormat.setColumnWidthConstraints(lengths);

    cursor.setBlockFormat(header);
    cursor.insertText("Сравнение аппаратов", mainHeaderFormat);

    cursor.movePosition(cursor.End);
    QTextTable *textTable = cursor.insertTable(rows, columns, tableFormat);
    QTextCharFormat tableHeaderFormat;
    for (int i=0;i<columns;i++)
    {
        QTextTableCell cell = textTable->cellAt(0,i);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(header);
        cellCursor.insertText(names[i],headerFormat);
    }
    for (int i=1;i<columns;i++)
    {
        QTextTableCell cell = textTable->cellAt(1,i);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(header);
        cellCursor.insertImage(images[i-1]);
    }
    for (int i=2;i<rows;i++)
        for (int j=0;j<columns;j++)
        {
            QTextTableCell cell = textTable->cellAt(i, j);
            cell.setFormat(tableHeaderFormat);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerAlignment);
            cellCursor.insertText(values[i][j],textFormat);
        }
    cursor.movePosition(cursor.End);
    cursor.movePosition(cursor.NextRow);
    cursor.movePosition(cursor.NextRow);
    cursor.setBlockFormat(header);
    cursor.insertText("Параметры сравнения", secondaryHeaderFormat);
    cursor.movePosition(cursor.NextRow);

    columns = compareValues[0].length();
    rows = compareValues.length();
    tableFormat.setWidth(950);
    verticalHeader = QTextLength(QTextLength::FixedLength,150);
    verticalCell = QTextLength(QTextLength::FixedLength,800/columns);
    lengths.clear();
    lengths.append(verticalHeader);
    for (int i=0;i<columns-1;i++)
        lengths.append(verticalCell);
    tableFormat.setColumnWidthConstraints(lengths);

    textTable = cursor.insertTable(rows, columns, tableFormat);
    for (int i=0;i<rows;i++)
        for (int j=0;j<columns;j++)
        {
            QTextTableCell cell = textTable->cellAt(i, j);
            cell.setFormat(tableHeaderFormat);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerAlignment);
            cellCursor.insertText(compareValues[i][j],textFormat);
        }
    cursor.movePosition(cursor.End);
    cursor.movePosition(cursor.NextRow);

    QSize tmpSize = chart1->size();
    chart1->resize(470,500);
    QPixmap p = chart1->grab();
    QImage img = p.toImage();
    img = img.scaled(470,500);
    cursor.insertImage(img);
    chart1->resize(tmpSize);

    tmpSize = chart2->size();
    chart2->resize(470,500);
    p = chart2->grab();
    img = p.toImage();
    img = img.scaled(470,500);
    cursor.insertImage(img);
    chart2->resize(tmpSize);

    doc.setDocumentMargin(0);
    doc.setTextWidth(4);
    fileManager = new FileManager();
    fileManager->printPDF(&doc, filePath);
    delete fileManager;
}
qreal TabCatalogAndComparisonModel::getNumberFromString(QString line, int param)
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
