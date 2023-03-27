#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "chartWidget.h"
#include <QVariant>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <ChartView.h>
#include <chartDialog.h>
#include <userLoginWindow.h>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/qpolarchart.h>
#include <QtCharts/QtCharts>

#include <QPrinter>
#include <fileProjectValue.h>
#include <tabPredictionModel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabPredictionModel = TabPredictionModel(&model);
    tabNewProjectModel = TabNewProjectModel(&model);
    tabEditDBModel = TabEditDBModel(&model);
    tabNewExtrasModel = TabNewExtrasModel(&model);
    tabNewCraftModel = TabNewCraftModel(&model);
    tabCatalogAndComparisonModel = TabCatalogAndComparisonModel(&model);
    rebuildTabs();
    //loginWindow = userLoginWindow(this);

    QObject::connect(&saveToPdfDialog,SIGNAL(startSave(QVector<QString>, int, int)),this,SLOT(saveToPdf(QVector<QString>, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rebuildTabs()
{
    buildDisplayTab();
    buildCompareTab();
    buildAddUnitTab();

    buildEditDBTab();
    buildEditProjectTab();
    buildAddExtrasTab();
    buildPredictionTab();

    startAuth();
}

QString MainWindow::startAuth()
{
    loginWindow.show();
}
//===============================================================================================================================================
//                                                          Display tab
//===============================================================================================================================================

void MainWindow::buildDisplayTab()
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->setColumnCount(1);
    tabCatalogAndComparisonModel.createNavigationTree(treeItem);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setHorizontalHeaderLabels({"Номер показателя", "Параметр", "Значение"});
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    int rowCount = ui->tableWidget->rowCount();

    int unitId = tabCatalogAndComparisonModel.getUnitIdByName(item->text(0));
    QVector<QPair<QString,QString>> values = tabCatalogAndComparisonModel.getUnitData(unitId);
    for (int i=0;i<values.length(); i++){
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount,1, new QTableWidgetItem(values[i].first));
        ui->tableWidget->setItem(rowCount,2, new QTableWidgetItem(values[i].second));
        rowCount++;
    }
    //---------------------
    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(tabCatalogAndComparisonModel.getUnitImageFromId(unitId).toUtf8()), "PNG");
    //QImage picture = QImage(tabCatalogAndComparisonModel.getUnitImageFromId(unitId_1));
    ui->label->setPixmap(image);
    //picture = QImage("C:\\Catalog\\Scheme");
    //ui->label_6->setPixmap(QPixmap::fromImage(picture));
    //---------------------
}
//===============================================================================================================================================
//
//===============================================================================================================================================
//===============================================================================================================================================
//                                                          Compare tab
//===============================================================================================================================================

void MainWindow::buildCompareTab()
{

    QStringList names = model.getNamesFromTableStringList("unit");
    ui->comboBox->addItems(names);
    ui->comboBox_2->addItems(names);
    ui->tableWidget_4->verticalHeader()->hide();
    ui->scrollArea_3->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    rebuildCompareTable(arg1, ui->comboBox_2->currentText());
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    rebuildCompareTable(ui->comboBox->currentText(), arg1);
}

void MainWindow::rebuildCompareTable(QString unitName1, QString unitName2)
{
    qDebug() << unitName1 << " " << unitName2;

    ui->label_7->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_8->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_4->clearContents();
    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setColumnCount(3); // Указываем число колонок
    ui->tableWidget_4->setShowGrid(false); // Включаем сетку
    ui->tableWidget_4->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->tableWidget_4->setHorizontalHeaderLabels({"Номер показателя", "Параметр", "Значение"});
    ui->tableWidget_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_4->setEditTriggers(QTableWidget::NoEditTriggers);

    int unitId_1 = tabCatalogAndComparisonModel.getUnitIdByName(unitName1);
    int unitId_2 = tabCatalogAndComparisonModel.getUnitIdByName(unitName2);
    QVector<QPair<QString,QString>> values_1 = tabCatalogAndComparisonModel.getUnitData(unitId_1);
    QVector<QPair<QString,QString>> values_2 = tabCatalogAndComparisonModel.getUnitData(unitId_2);
    QVector<QPair<QString,QStringList>> compareVector = tabCatalogAndComparisonModel.formCompareTable(values_1, values_2);
    int rowCount = 0;
    for (int i=0;i<compareVector.length(); i++){
            ui->tableWidget_4->insertRow(rowCount);
            ui->tableWidget_4->setItem(rowCount,0, new QTableWidgetItem(compareVector[i].first));
            ui->tableWidget_4->setItem(rowCount,1, new QTableWidgetItem(compareVector[i].second[0]));
            ui->tableWidget_4->setItem(rowCount,2, new QTableWidgetItem(compareVector[i].second[1]));
            rowCount++;
    }

    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(tabCatalogAndComparisonModel.getUnitImageFromId(unitId_1).toUtf8()), "PNG");
    //QImage picture = QImage(tabCatalogAndComparisonModel.getUnitImageFromId(unitId_1));
    ui->label_7->setPixmap(image.scaled(ui->comboBox->width()/2,ui->comboBox->width()/2,Qt::KeepAspectRatio));
    image.loadFromData(QByteArray::fromBase64(tabCatalogAndComparisonModel.getUnitImageFromId(unitId_2).toUtf8()), "PNG");
    //picture = QImage(tabCatalogAndComparisonModel.getUnitImageFromId(unitId_2));
    ui->label_8->setPixmap(image.scaled(ui->comboBox->width()/2,ui->comboBox->width()/2,Qt::KeepAspectRatio));

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setColumnWidth(1,ui->tableWidget_4->width()/2);
    comparator.clearValues();
    comparator.addUnitName(unitName1);
    comparator.addUnitName(unitName2);
}

void MainWindow::on_tableWidget_4_cellDoubleClicked(int row, int column)
{
    QColor color;
    if (ui->tableWidget_4->item(row,column)->backgroundColor() == Qt::yellow)
    {
        comparator.removeValuesFromComparison(ui->tableWidget_4->item(row,0)->text());
        color = Qt::white;
    }
    else if (ui->tableWidget_4->item(row,column)->backgroundColor() == Qt::green)
    {
        comparator.removeValuesFromComparison(ui->tableWidget_4->item(row,0)->text());
        QVector <qreal> tmpValues;
        for (int i = 1;i<ui->tableWidget_4->columnCount();i++)
            tmpValues.append(1/tabCatalogAndComparisonModel.getNumberFromString(ui->tableWidget_4->item(row,i)->text(),0));

        comparator.addValuesToComparison(ui->tableWidget_4->item(row,0)->text(), tmpValues);
        color = Qt::yellow;
    }
    else
    {
        QVector <qreal> tmpValues;
        for (int i = 1;i<ui->tableWidget_4->columnCount();i++)
            tmpValues.append(tabCatalogAndComparisonModel.getNumberFromString(ui->tableWidget_4->item(row,i)->text(),0));
        comparator.addValuesToComparison(ui->tableWidget_4->item(row,0)->text(), tmpValues);

        color = Qt::green;
    }

    for(int i=0;i<ui->tableWidget_4->columnCount();i++){
        ui->tableWidget_4->item(row,i)->setBackgroundColor(color);
    }
    tabCatalogAndComparisonModel.getNumberFromString(ui->tableWidget_4->item(row,column)->text());
    buildChart();
    buildChartTable();
}

void MainWindow::on_pushButton_clicked()
{
    buildChart();
}

void MainWindow::buildChartTable()
{
    ui->tableWidget_5->clearContents();
    ui->tableWidget_5->setRowCount(0);
    ui->tableWidget_5->setColumnCount(3);
    ui->tableWidget_5->setShowGrid(true);
    ui->tableWidget_5->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_5->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_5->setEditTriggers(QTableWidget::NoEditTriggers);
    QVector<CompareValue> tableValues = comparator.getValues();
    for (int i=0;i<tableValues.length();i++){
        ui->tableWidget_5->insertRow(i);
        ui->tableWidget_5->setItem(i,0, new QTableWidgetItem(tableValues[i]._parameter));
        for(int j=0;j<tableValues[0]._values.length();j++){
            ui->tableWidget_5->setItem(i,j+1, new QTableWidgetItem(QString::number(tableValues[i]._values[j])));
        }
    }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ПЕРЕНЕСТИ В МОДЕЛЬ
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void MainWindow::buildChart()
{
    if (comparator.isEmpty()) return ;
    //model.
    QPair<qreal,qreal> minMax = comparator.getMinMax();
    const qreal angularMin = 0;
    const qreal angularMax = 10;

    const qreal radialMin = minMax.first;
    const qreal radialMax = minMax.second;

    //qDebug()<<radialMin<<radialMax;
    QPolarChart *chart = new QPolarChart();
    QVector <QLineSeries*> seriesSummary = comparator.CreateChart();
    for (int i=0;i<seriesSummary.length();i++){
        qDebug() << seriesSummary[i];
        chart->addSeries(seriesSummary[i]);
    }

    chart->setTitle("Сравнение аппаратов");

    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(0);
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    angularAxis->setMax(angularMax);
    angularAxis->setMin(angularMin);
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(0);
    radialAxis->setLabelFormat("%d");
    radialAxis->setMax(angularMax);
    radialAxis->setMin(angularMin);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    //chartDialog *chartdialog = new chartDialog(this, chart);
    //chartdialog->show();
    ui->widget->setChart(chart);
    qDebug()<<"";
    qDebug()<<"MinMax"<<radialMin<<radialMax;
}
//===============================================================================================================================================
//
//===============================================================================================================================================
//===============================================================================================================================================
//                                                          Add unit tab
//===============================================================================================================================================
void MainWindow::buildAddUnitTab()
{
    QStringList names = model.getNamesFromTableStringList("unit");
    ui->comboBoxUnitClass->addItems({"РН", "РБ", "КА"});
    ui->comboBoxUnitProject->addItems({"Проектный", "Не проектный"});

    QStringList organizationNames = model.getNamesFromTableStringList("organization");

    ui->comboBoxUnitCustomer->addItems(organizationNames);
    ui->comboBoxUnitDeveloperId->addItems(organizationNames);
    ui->comboBoxUnitExtraDeveloperId->addItems(organizationNames);
    ui->comboBoxUnitManufacturerId->addItems(organizationNames);
    QStringList spaceportNames = model.getNamesFromTableStringList("spaceport");

    ui->comboBoxUnitFirstLaunchSpaceport->addItems(spaceportNames);
    ui->comboBox_10->addItem("Добавить новый аппарат");
    ui->comboBox_10->addItems(model.QVectorToQStringList(model.getNamesFromTable("unit")));
    ui->label_53->setVisible(false);
}

void MainWindow::on_comboBox_10_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Добавить новый аппарат" && ui->comboBox_10->currentIndex()==0){
        addUnitTabUpdateValues();
        ui->label_53->setText(QString::number(-1));
        ui->pushButton_2->setText("Добавить");
    }
    else
    {
        DBUnit currentUnit = tabNewCraftModel.getUnitDataByName(arg1);
        ui->comboBoxUnitClass->setCurrentIndex(ui->comboBoxUnitClass->findText(currentUnit.unit_class()));
        ui->lineEditUnitName->setText(currentUnit.name());
        ui->textEditUnitPurpose->setPlainText(currentUnit.purpose());
        if (currentUnit.project() == 1)
            ui->comboBoxUnitProject->setCurrentIndex(ui->comboBoxUnitProject->findText("Проектный"));
        else
            ui->comboBoxUnitProject->setCurrentIndex(ui->comboBoxUnitProject->findText("Не проектный"));
        ui->textEditUnitObjective->setPlainText(currentUnit.objective());
        ui->lineEditUnitWorkStatus->setText(currentUnit.work_status());
        ui->comboBoxUnitDeveloperId->setCurrentIndex(ui->comboBoxUnitDeveloperId->findText(tabNewCraftModel.getOrganizationById(currentUnit.developer_id()).name()));
        ui->comboBoxUnitExtraDeveloperId->setCurrentIndex(ui->comboBoxUnitExtraDeveloperId->findText(tabNewCraftModel.getOrganizationById(currentUnit.extra_developer_id()).name()));
        ui->comboBoxUnitManufacturerId->setCurrentIndex(ui->comboBoxUnitManufacturerId->findText(tabNewCraftModel.getOrganizationById(currentUnit.manufacturer_id()).name()));
        ui->spinBoxUnitLaunches->setValue(currentUnit.launches());
        ui->comboBoxUnitCustomer->setCurrentIndex(ui->comboBoxUnitCustomer->findText(tabNewCraftModel.getOrganizationById(currentUnit.customer_id()).name()));
        ui->spinBoxUnitSuccessfulLaunches->setValue(currentUnit.successful());
        ui->dateTimeEditFirstLaunch->setDateTime(currentUnit.first_launch());
        ui->comboBoxUnitFirstLaunchSpaceport->setCurrentIndex(ui->comboBoxUnitFirstLaunchSpaceport->findText(tabNewCraftModel.getSpaceportById(currentUnit.first_launch_spaceport_id()).name()));
        ui->lineEditFinancingType->setText(currentUnit.financing_type());
        ui->lineEditControlSystem->setText(currentUnit.control_system_type());
        //ui->labelUnitImageURL->setText(currentUnit.image_url());
        ui->doubleSpinBoxUnitPrice->setValue(currentUnit.price());
        ui->spinBoxUnitPriceYear->setValue(currentUnit.price_year());
        QString unitClass = ui->comboBoxUnitClass->currentText();
        if (unitClass == "РН")
        {
            DBBooster_rocket currentBR = tabNewCraftModel.getBoosterRocketById(currentUnit.id());
            maxPayloadField->setValue(currentBR.max_payload());
            minPayloadField->setValue(currentBR.min_payload());
            econInfoField->setText(currentBR.econ_info());
            physInfoField->setText(currentBR.phys_info());
        }
        else if (unitClass == "РБ")
        {
            DBUpper_block currentUB = tabNewCraftModel.getUpperBlockById(currentUnit.id());
            econInfoField->setText(currentUB.econ_info());
            physInfoField->setText(currentUB.phys_info());
        }
        else if (unitClass == "КА")
        {
            DBSpacecraft currentSC = tabNewCraftModel.getSpacecraftById(currentUnit.id());
            econInfoField->setText(currentSC.econ_info());
            physInfoField->setText(currentSC.phys_info());
            weightField->setValue(currentSC.weight());
            activeLifetimeField->setValue(currentSC.active_lifetime());
        }
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(currentUnit.image_url().toUtf8()), "PNG");
        ui->label_12->setPixmap(image);
        ui->label_53->setText(QString::number(currentUnit.id()));
        ui->pushButton_2->setText("Сохранить");
    }
}

void MainWindow::addUnitTabUpdateValues()
{

}

void MainWindow::on_comboBoxUnitClass_currentIndexChanged(const QString &arg1)
{
    qDebug()<<ui->formLayout_3->rowCount();
    int rowCount = ui->formLayout_3->rowCount();
    for (int i=0;i<rowCount;i++) ui->formLayout_3->removeRow(0);
    if (arg1 == "РН")
    {
        maxPayloadField = new QDoubleSpinBox();
        minPayloadField = new QDoubleSpinBox();
        physInfoField = new QTextEdit();
        econInfoField = new QTextEdit();

        ui->formLayout_3->addRow(new QLabel("Максимальная грузоподъемность"), maxPayloadField);
        ui->formLayout_3->addRow(new QLabel("Минимальная грузоподъемность"), minPayloadField);
        ui->formLayout_3->addRow(new QLabel("Физические характеристики"), physInfoField);
        ui->formLayout_3->addRow(new QLabel("Экономические характеристики"), econInfoField);
    }
    else if(arg1 == "РБ")
    {
        physInfoField = new QTextEdit();
        econInfoField = new QTextEdit();
        ui->formLayout_3->addRow(new QLabel("Физические характеристики"), physInfoField);
        ui->formLayout_3->addRow(new QLabel("Экономические характеристики"), econInfoField);
    }
    else if(arg1 == "КА")
    {
        weightField = new QDoubleSpinBox();
        activeLifetimeField = new QDoubleSpinBox();
        physInfoField = new QTextEdit();
        econInfoField = new QTextEdit();
        ui->formLayout_3->addRow(new QLabel("Вес"), weightField);
        ui->formLayout_3->addRow(new QLabel("САС"), activeLifetimeField);
        ui->formLayout_3->addRow(new QLabel("Физические характеристики"), physInfoField);
        ui->formLayout_3->addRow(new QLabel("Экономические характеристики"), econInfoField);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите изображение", "C://", "*.png *.jpg *.gif");
    QImage picture = QImage(filePath);
    ui->label_12->setPixmap(QPixmap::fromImage(picture));
    ui->labelUnitImageURL->setText(filePath);
}

void MainWindow::on_pushButton_2_clicked()
{
    int maxPayload = 0;
    int minPayload = 0;
    qreal weight = 0;
    qreal activeLifetime = 0;
    QString physInfo = "";
    QString econInfo = "";
    QString unitClass = ui->comboBoxUnitClass->currentText();
    if (unitClass == "РН")
    {
        maxPayload = maxPayloadField->value();
        minPayload = minPayloadField->value();
        econInfo = econInfoField->toPlainText();
        physInfo = physInfoField->toPlainText();
    }
    else if (unitClass == "РБ")
    {
        econInfo = econInfoField->toPlainText();
        physInfo = physInfoField->toPlainText();
    }
    else if (unitClass == "КА")
    {
        weight = weightField->value();
        activeLifetime = activeLifetimeField->value();
        econInfo = econInfoField->toPlainText();
        physInfo = physInfoField->toPlainText();
    }
    QByteArray image;
    QBuffer buffer(&image);
    buffer.open(QBuffer::WriteOnly);
    QImage(ui->labelUnitImageURL->text()).save(&buffer, "PNG");
    if (ui->label_53->text().toInt() == -1)
    {
        tabNewCraftModel.addUnitToDB(
                    ui->comboBoxUnitClass->currentText(),
                    ui->lineEditUnitName->text(),
                    ui->textEditUnitPurpose->toPlainText(),
                    ui->comboBoxUnitProject->currentText(),
                    ui->textEditUnitObjective->toPlainText(),
                    ui->lineEditUnitWorkStatus->text(),
                    ui->comboBoxUnitDeveloperId->currentText(),
                    ui->comboBoxUnitExtraDeveloperId->currentText(),
                    ui->comboBoxUnitManufacturerId->currentText(),
                    ui->spinBoxUnitLaunches->value(),
                    ui->comboBoxUnitCustomer->currentText(),
                    ui->spinBoxUnitSuccessfulLaunches->value(),
                    ui->dateTimeEditFirstLaunch->dateTime(),
                    ui->comboBoxUnitFirstLaunchSpaceport->currentText(),
                    ui->lineEditFinancingType->text(),
                    ui->lineEditControlSystem->text(),
                    image.toBase64(),
                    ui->doubleSpinBoxUnitPrice->value(),
                    ui->spinBoxUnitPriceYear->value(),
                    maxPayload,
                    minPayload,
                    weight,
                    activeLifetime,
                    econInfo,
                    physInfo);
        rebuildTabs();
    }
    else
    {
        tabNewCraftModel.updateUnitDB(
                    ui->label_53->text().toInt(),
                    ui->comboBoxUnitClass->currentText(),
                    ui->lineEditUnitName->text(),
                    ui->textEditUnitPurpose->toPlainText(),
                    ui->comboBoxUnitProject->currentText(),
                    ui->textEditUnitObjective->toPlainText(),
                    ui->lineEditUnitWorkStatus->text(),
                    ui->comboBoxUnitDeveloperId->currentText(),
                    ui->comboBoxUnitExtraDeveloperId->currentText(),
                    ui->comboBoxUnitManufacturerId->currentText(),
                    ui->spinBoxUnitLaunches->value(),
                    ui->comboBoxUnitCustomer->currentText(),
                    ui->spinBoxUnitSuccessfulLaunches->value(),
                    ui->dateTimeEditFirstLaunch->dateTime(),
                    ui->comboBoxUnitFirstLaunchSpaceport->currentText(),
                    ui->lineEditFinancingType->text(),
                    ui->lineEditControlSystem->text(),
                    image.toBase64(),
                    ui->doubleSpinBoxUnitPrice->value(),
                    ui->spinBoxUnitPriceYear->value(),
                    maxPayload,
                    minPayload,
                    weight,
                    activeLifetime,
                    econInfo,
                    physInfo);
    }

}

//===============================================================================================================================================
//
//===============================================================================================================================================
//===============================================================================================================================================
//                                                          Add extras tab
//===============================================================================================================================================

void MainWindow::buildAddExtrasTab()
{
    ui->tableWidget_9->clearContents();
    ui->tableWidget_9->setRowCount(0);
    ui->tableWidget_9->setColumnCount(18); // Указываем число колонок
    ui->tableWidget_9->setShowGrid(true); // Включаем сетку
    ui->tableWidget_9->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_9->setHorizontalHeaderLabels({"","2024","2025","2026","2027","2028","2029","2030","2031","2032","2033","2034","2035","2036","2037","2038","2039","2040"});
    ui->tableWidget_9->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_9->insertRow(0);
    ui->tableWidget_9->setItem(0, 0,  new QTableWidgetItem("Цены"));
    ui->comboBox_4->addItems({"Связь", "ДЗЗ", "ФКИ", "Другое"});
    ui->comboBox_9->addItems(model.getNamesFromTableStringList("unit"));
    ui->comboBox_6->addItems(tabNewExtrasModel.getUnitNamesByTypeStringList("РН"));
    ui->comboBox_7->addItems(tabNewExtrasModel.getUnitNamesByTypeStringList("РБ"));
    ui->comboBox_8->addItems(model.getNamesFromTableStringList("spaceport"));
}

void MainWindow::on_pushButton_5_clicked()
{
    tabNewExtrasModel.addOrganizationToDB(ui->lineEdit_6->text());
}

void MainWindow::on_pushButton_6_clicked()
{
     tabNewExtrasModel.addSpaceportToDB(ui->lineEdit_7->text());
}

void MainWindow::on_comboBox_6_currentIndexChanged(const QString &arg1)
{
    rebuildEditLaunchTable(arg1, ui->comboBox_7->currentText(), ui->comboBox_8->currentText());
}


void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
    rebuildEditLaunchTable(ui->comboBox_6->currentText(), arg1, ui->comboBox_8->currentText());
}


void MainWindow::on_comboBox_8_currentIndexChanged(const QString &arg1)
{
    rebuildEditLaunchTable(ui->comboBox_6->currentText(), ui->comboBox_7->currentText(), arg1);
}

void MainWindow::rebuildEditLaunchTable(QString boosterRocket, QString upperBlock, QString spaceport)
{
    if (boosterRocket != "" && upperBlock != "" && spaceport != "")
    {
        DBlaunch currentLaunch = tabNewExtrasModel.getLaunchFromParamIds(boosterRocket,upperBlock, spaceport);

        ui->doubleSpinBox->setValue(currentLaunch.delivery_price());
        ui->doubleSpinBox_2->setValue(currentLaunch.launch_price());
        ui->doubleSpinBox_3->setValue(currentLaunch.min_payload());
        ui->doubleSpinBox_4->setValue(currentLaunch.max_payload());
        ui->spinBox_2->setValue(currentLaunch.price_year());
        QVector<qreal> prices = tabNewExtrasModel.pricesToVector(currentLaunch.prices());
        for (int i=1;i<ui->tableWidget_9->columnCount();i++)
        {
            ui->tableWidget_9->setItem(0, i,  new QTableWidgetItem(QString::number(prices[i])));
        }

    }
}



//===============================================================================================================================================
//
//===============================================================================================================================================
//===============================================================================================================================================
//                                                          Edit tab
//===============================================================================================================================================

void MainWindow::buildEditDBTab()
{
    ui->comboBox_3->addItems(tabEditDBModel.getTableDescriptionsStringList());
    dbValuesToChange.clear();
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    readyToStore = false;
    ui->tableWidget_6->clearContents();
    ui->tableWidget_6->setRowCount(0);

    ui->tableWidget_6->setColumnCount(tabEditDBModel.getTableColumnCount(arg1)); // Указываем число колонок
    ui->tableWidget_6->setShowGrid(true); // Включаем сетку
    ui->tableWidget_6->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_6->setHorizontalHeaderLabels(tabEditDBModel.getTableColumnNamesStringList(arg1));
    ui->tableWidget_6->horizontalHeader()->setStretchLastSection(true);
    //ui->tableWidget_6->setEditTriggers(QTableWidget::NoEditTriggers);

    QVector <QVector<QString>> values = tabEditDBModel.getValuesFromTable(ui->comboBox_3->currentText(), ui->tableWidget_6->columnCount());
    for (int i=0;i<values.length(); i++){
        int rowCount = ui->tableWidget_6->rowCount();
        ui->tableWidget_6->insertRow(rowCount);
        for (int j=0;j<values[i].length();j++){
            ui->tableWidget_6->setItem(rowCount,j, new QTableWidgetItem(values[i][j]));
        }
    }

    readyToStore = true;
    dbValuesToChange.clear();
}

void MainWindow::on_tableWidget_6_itemChanged(QTableWidgetItem *item)
{
    if (readyToStore){
        dbValuesToChange.append(dbChangeValue(
                                    ui->tableWidget_6->item(item->row(),0)->text(),
                                    ui->tableWidget_6->horizontalHeaderItem(item->column())->text(),
                                    item->text()));
        qDebug()<<ui->tableWidget_6->item(item->row(),0)->text()<<item->text();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    qDebug() << tabEditDBModel.updateDataInTable(ui->comboBox_3->currentText(), dbValuesToChange);
    rebuildTabs();
}




//===============================================================================================================================================
//
//===============================================================================================================================================
//===============================================================================================================================================
//                                                          Edit Project tab
//===============================================================================================================================================

void MainWindow::buildEditProjectTab()
{

    ui->tableWidget_7->clearContents();
    ui->tableWidget_7->setRowCount(0);

    ui->tableWidget_7->setColumnCount(18); // Указываем число колонок
    ui->tableWidget_7->setShowGrid(true); // Включаем сетку
    ui->tableWidget_7->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_7->setHorizontalHeaderLabels({"","2024","2025","2026","2027","2028","2029","2030","2031","2032","2033","2034","2035","2036","2037","2038","2039","2040"});
    ui->tableWidget_7->horizontalHeader()->setStretchLastSection(true);
    //ui->tableWidget_6->setEditTriggers(QTableWidget::NoEditTriggers);

    int rowCount = ui->tableWidget_7->rowCount();
    ui->tableWidget_7->insertRow(rowCount);
    ui->tableWidget_7->insertRow(rowCount+1);
    ui->tableWidget_7->insertRow(rowCount+2);
    ui->tableWidget_7->insertRow(rowCount+3);
    ui->tableWidget_7->insertRow(rowCount+4);
    ui->tableWidget_7->setItem(rowCount, 0,  new QTableWidgetItem("ЭП, КД, Макет, испытания"));
    ui->tableWidget_7->setItem(rowCount+1, 0,  new QTableWidgetItem("Создание первого ОКР КА"));
    ui->tableWidget_7->setItem(rowCount+2, 0,  new QTableWidgetItem("Создание последнего ОКР КА"));
    ui->tableWidget_7->setItem(rowCount+3, 0,  new QTableWidgetItem("НЭО, документация"));
    ui->tableWidget_7->setItem(rowCount+4, 0,  new QTableWidgetItem("Создание серийного образца"));
    ui->comboBox_5->addItems(model.getNamesFromTableStringList("project"));
}

void MainWindow::on_pushButton_9_clicked()
{
    tabNewProjectModel.addProjectToDB(ui->lineEdit_2->text(),ui->comboBox_4->currentText(), ui->comboBox_9->currentText());
    buildEditProjectTab();
}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    QVector<QVector<qreal>> prices = tabNewProjectModel.getProjectPricesFromName(arg1);
    for (int i=0;i<5; i++){
        for (int j=1;j<prices[i].length();j++){
            ui->tableWidget_7->setItem(i, j, new QTableWidgetItem(QString::number(prices[i][j-1])));
        }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    QVector<qreal> pre_prices, first_unit_prices, last_unit_prices, post_prices, serial_prices;
    for (int i=1;i<ui->tableWidget_7->columnCount();i++)
    {
        pre_prices.append(ui->tableWidget_7->item(0,i)->text().toDouble());
        first_unit_prices.append(ui->tableWidget_7->item(1,i)->text().toDouble());
        last_unit_prices.append(ui->tableWidget_7->item(2,i)->text().toDouble());
        post_prices.append(ui->tableWidget_7->item(3,i)->text().toDouble());
        serial_prices.append(ui->tableWidget_7->item(4,i)->text().toDouble());
    }

    qDebug()<<pre_prices<<first_unit_prices<<last_unit_prices<<post_prices<<serial_prices;
    tabNewProjectModel.updateProjectInfo(ui->comboBox_5->currentText(), pre_prices, first_unit_prices, last_unit_prices, post_prices, serial_prices);
}

//===============================================================================================================================================
//
//===============================================================================================================================================

//===============================================================================================================================================
//                                                          Prediction tab
//===============================================================================================================================================


void MainWindow::buildPredictionTab()
{
    ui->listWidget->clear();
    ui->tableWidget_8->clear();
    tabPredictionModel.projectModelClear();
    predictionTableEditedByUser = false;
    listWidgetEditedByUser = false;
    QStringList projectNames = model.getNamesFromTableStringList("project");
    ui->listWidget->addItems(projectNames);
    for(int i=0;i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setFlags(ui->listWidget->item(i)->flags() | Qt::ItemIsUserCheckable);
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
    ui->tableWidget_8->clearContents();
    ui->tableWidget_8->setRowCount(0);

    ui->tableWidget_8->setColumnCount(18); // Указываем число колонок
    ui->tableWidget_8->setShowGrid(true); // Включаем сетку
    ui->tableWidget_8->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_8->setHorizontalHeaderLabels({"","2024","2025","2026","2027","2028","2029","2030","2031","2032","2033","2034","2035","2036","2037","2038","2039","2040"});
    ui->tableWidget_8->horizontalHeader()->setStretchLastSection(true);

    //QVector<QVector<qreal>> prices = model.getProjectPricesFromName(arg1);

    int rowCount = ui->tableWidget_8->rowCount();
    ui->tableWidget_8->insertRow(rowCount);
    ui->tableWidget_8->insertRow(rowCount+1);
    ui->tableWidget_8->insertRow(rowCount+2);
    ui->tableWidget_8->insertRow(rowCount+3);
    ui->tableWidget_8->insertRow(rowCount+4);
    ui->tableWidget_8->insertRow(rowCount+5);
    ui->tableWidget_8->insertRow(rowCount+6);


    for (int i=0;i<ui->tableWidget_8->columnCount();i++)
    {
        ui->tableWidget_8->setItem(rowCount, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+1, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+2, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+3, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+4, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+5, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->setItem(rowCount+6, i,  new QTableWidgetItem(""));
        ui->tableWidget_8->item(rowCount, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+1, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+2, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+3, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+4, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+5, i)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_8->item(rowCount+6, i)->setFlags(Qt::ItemIsEnabled);
    }
    ui->tableWidget_8->item(rowCount, 0)->setText("Связь");
    ui->tableWidget_8->item(rowCount+1, 0)->setText("ДЗЗ");
    ui->tableWidget_8->item(rowCount+2, 0)->setText("ФКИ");
    ui->tableWidget_8->item(rowCount+3, 0)->setText("Другое");
    ui->tableWidget_8->item(rowCount+4, 0)->setText("Цены КА");
    ui->tableWidget_8->item(rowCount+5, 0)->setText("Цены РН");
    ui->tableWidget_8->item(rowCount+6, 0)->setText("Итого");
    setTableWidgetRowColor(ui->tableWidget_8, rowCount,0,QColor(255,239,214));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+1,0,QColor(255,239,214));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+2,0,QColor(255,239,214));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+3,0,QColor(255,239,214));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+4,0,QColor(244,244,255));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+5,0,QColor(244,244,255));
    setTableWidgetRowColor(ui->tableWidget_8, rowCount+6,0,QColor(244,244,255));

    listWidgetEditedByUser = true;
    predictionTableEditedByUser = true;
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{

    if (listWidgetEditedByUser)
    {
        predictionTableEditedByUser = false;
        int rowCount = ui->tableWidget_8->rowCount();
        if (item->checkState()==Qt::Checked)
        {

            int index = tabPredictionModel.projectModelAddProject(item->text());
            //int unitLifetime = model.projectModelGetUnitLifetime(item->text());

            for (int i=0;i<7;i++)
            {
                 ui->tableWidget_8->insertRow(i + index);
            }
            for (int i=0;i<ui->tableWidget_8->columnCount();i++)
                for (int j=index;j<7 + index;j++)
                    ui->tableWidget_8->setItem(j, i,  new QTableWidgetItem(""));

            for (int i=0;i<ui->tableWidget_8->columnCount();i++)
            {
                ui->tableWidget_8->item(index, i)->setFlags(Qt::ItemIsEnabled);
                ui->tableWidget_8->item(index+5, i)->setFlags(Qt::ItemIsEnabled);
                ui->tableWidget_8->item(index+6, i)->setFlags(Qt::ItemIsEnabled);
            }
            ui->tableWidget_8->setItem(index, 0,  new QTableWidgetItem(item->text())); //+" (САС "+QString::number(unitLifetime)+" лет)")


            ui->tableWidget_8->item(index, 1)->setFlags(Qt::ItemIsEnabled);

            ui->tableWidget_8->setItem(1 + index, 0,  new QTableWidgetItem("Запуск ОКР аппаратов"));
            ui->tableWidget_8->setItem(2 + index, 0,  new QTableWidgetItem("Запуск серийных аппаратов"));
            ui->tableWidget_8->setItem(3 + index, 0,  new QTableWidgetItem("Блок КА"));
            ui->tableWidget_8->setItem(4 + index, 0,  new QTableWidgetItem("Ракета-носитель"));
            ui->tableWidget_8->setItem(5 + index, 0,  new QTableWidgetItem("Цены КА ОКР+Серия"));
            ui->tableWidget_8->setItem(6 + index, 0,  new QTableWidgetItem("Цены РН проекта"));
            ui->tableWidget_8->item(1 + index, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget_8->item(2 + index, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget_8->item(3 + index, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget_8->item(4 + index, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget_8->item(5 + index, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget_8->item(6 + index, 0)->setFlags(Qt::ItemIsEnabled);
            setTableWidgetRowColor(ui->tableWidget_8, index, 0, QColor(255,245,224));
            setTableWidgetRowColor(ui->tableWidget_8, index + 5, 0, QColor(244,244,255));
            setTableWidgetRowColor(ui->tableWidget_8, index + 6, 0, QColor(244,244,255));
            QStringList launches = tabPredictionModel.getValidLaunchesNamesStringList();
            for (int i=1;i<ui->tableWidget_8->columnCount();i++)
            {
                QComboBox *a = new QComboBox();
                a->addItems(launches);
                a->setProperty("spaceCraft", item->text());

                QObject::connect(a,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_tableWidget_8_comboBox_index_changed(const QString &)));
                ui->tableWidget_8->setCellWidget(4 + index,i,a);
            }
        }
        else
        {
            int projectNumber = tabPredictionModel.projectModelGetProjectNumber(item->text());
            qDebug() << projectNumber;
            for (int i=0;i<7; i++)
                 ui->tableWidget_8->removeRow(projectNumber);
            tabPredictionModel.projectModelRemoveProject(item->text());
            for (int i=0;i<7;i++){
                 ui->tableWidget_8->removeRow(rowCount-3);
            }
        }
        predictionTableEditedByUser = true;
    }

}

void MainWindow::on_pushButton_17_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "C://", "*.scn");
    if (filePath != "")
    {
        saveToFile(filePath);
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    if (saveFilePath == "")
    {
        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "C://", "*.scn");
        if (filePath != "")
        {
            saveToFile(filePath);
        }
    }
    else
    {
        saveToFile(saveFilePath);
    }
}

void MainWindow::saveToFile(QString filePath)
{
    QString projectName;
    QVector<QString> launchValues;
    QVector<int> okrYears, serialYears, unitBlock;
    QVector<FileProjectValue> saveValues;
    for (int i=0;i<ui->tableWidget_8->rowCount();i++)
    {
        if (ui->tableWidget_8->item(i,0)->backgroundColor() == QColor(255,245,224))
        {
            projectName = ui->tableWidget_8->item(i,0)->text();
            for (int j=1;j<ui->tableWidget_8->columnCount();j++)
            {
                okrYears.append(ui->tableWidget_8->item(i+1,j)->text().toInt());
                serialYears.append(ui->tableWidget_8->item(i+2,j)->text().toInt());
                unitBlock.append(ui->tableWidget_8->item(i+3,j)->text().toInt());
                launchValues.append(qobject_cast <QComboBox*> (ui->tableWidget_8->cellWidget(i+4,j))->currentText());
            }
            FileProjectValue tmpVal = FileProjectValue(projectName,okrYears,serialYears,unitBlock,launchValues);
            saveValues.append(tmpVal);
            okrYears.clear();
            serialYears.clear();
            unitBlock.clear();
            launchValues.clear();
        }
    }
    tabPredictionModel.saveToFile(saveValues, filePath);
    saveFilePath = filePath;
}

void MainWindow::on_pushButton_14_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть", "C://", "*.scn");
    if (filePath != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Сохранить", "Сохранить файл?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
        {
            if (saveFilePath != "")
            {
                saveToFile(saveFilePath);
            }
            else
            {
                QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "C://", "*.scn");
                if (filePath != "")
                {
                    saveToFile(filePath);
                }
                else return;
            }
        }
        else if (reply == QMessageBox::No)
        {

        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
        //Спросить сохранить или нет


        buildPredictionTab();
        QVector<FileProjectValue> values = tabPredictionModel.loadFromFile(filePath);
        QVector<QString> checkedProjects;
        for (int i=0;i<values.length();i++)
        {
            checkedProjects.append(values[i].getProjectName());
        }
        for (int i=0;i<ui->listWidget->count();i++)
        {
            if (checkedProjects.contains(ui->listWidget->item(i)->text()))
                ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }
        for (int i=0;i<values.length();i++)
        {
            for (int j=0;j<ui->tableWidget_8->rowCount();j++)
            {
                if (ui->tableWidget_8->item(j,0)->text()==values[i].getProjectName())
                {
                    for (int k=1;k<ui->tableWidget_8->columnCount();k++)
                    {
                        if (values[i].getOkrYears()[k-1]!=0)
                            ui->tableWidget_8->item(j+1,k)->setText(QString::number(values[i].getOkrYears()[k-1]));
                        if (values[i].getSerialYears()[k-1]!=0)
                            ui->tableWidget_8->item(j+2,k)->setText(QString::number(values[i].getSerialYears()[k-1]));
                        if (values[i].getUnitBlocks()[k-1]!=0)
                            ui->tableWidget_8->item(j+3,k)->setText(QString::number(values[i].getUnitBlocks()[k-1]));
                        qobject_cast <QComboBox*> (ui->tableWidget_8->cellWidget(j+4,k))->setCurrentIndex(qobject_cast <QComboBox*> (ui->tableWidget_8->cellWidget(j+4,k))->findText(values[i].getLaunchValues()[k-1]));
                    }
                }
            }
        }
        saveFilePath = filePath;
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    saveToPdfDialog.show();
    this->setEnabled(false);
}

void MainWindow::saveToPdf(QVector<QString> values, int startYear, int endYear)
{
    const int columns = ui->tableWidget_8->columnCount();
    const int rows = ui->tableWidget_8->rowCount();
    QTextDocument doc;
    QTextCursor cursor(&doc);
    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(1);
    tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
    tableFormat.clearColumnWidthConstraints();
    QTextTable *textTable = cursor.insertTable(rows + 1, columns, tableFormat);
    QTextCharFormat tableHeaderFormat;
    tableHeaderFormat.setBackground(QColor("#DADADA"));
    for (int i = 0; i < columns; i++) {
        QTextTableCell cell = textTable->cellAt(0, i);
        cell.setFormat(tableHeaderFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(ui->tableWidget_8->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString());
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            QTableWidgetItem *item = ui->tableWidget_8->item(i, j);
//            if (!item || item->text().isEmpty()) {
//                ui->tableWidget_8->setItem(i, j, new QTableWidgetItem("0"));
//            }

            QTextTableCell cell = textTable->cellAt(i, j);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText("asda");
            //ui->tableWidget_8->item(i, j)->text()
        }
    }
    cursor.movePosition(QTextCursor::End);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName("testpdf.pdf");
    doc.setDocumentMargin(0);
    doc.setTextWidth(5);
    doc.print(&printer);
    saveToPdfDialog.hide();
    this->setEnabled(true);
}


//===============================================================================================================================================
//
//===============================================================================================================================================



void MainWindow::setTableWidgetRowColor(QTableWidget *tableWidget, int row, int startColumn, QColor color)
{
    for (int i=startColumn;i<tableWidget->columnCount();i++){
        tableWidget->item(row,i)->setBackground(color);
    }
}

void MainWindow::on_tableWidget_8_comboBox_index_changed(const QString &)
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    emit on_tableWidget_8_cellChanged(-1,-1, cb->property("spaceCraft").toString());
}

void MainWindow::on_tableWidget_8_cellChanged(int row, int column, QString spaceCraft)
{
    if (predictionTableEditedByUser)
    {
        qDebug() << "adss";
        QRegExp number("\\d*");
        if ((row==-1) && (column==-1))
        {
            for (int i=0; i<ui->tableWidget_8->rowCount();i++)
            {
                if (ui->tableWidget_8->item(i,0)->text() == spaceCraft)
                {
                    row = i+1;
                    column = 1;
                    break;
                }
            }
        }
        if (number.exactMatch(ui->tableWidget_8->item(row,column)->text())) // is number
        {
            QVector<QVector<int>> yearsValues;
            QVector<QString> boosterRocketValues;
            int startRow = row;
            QString currentRowTextValue = ui->tableWidget_8->item(row,0)->text();
            bool brChanged = false;
            if (currentRowTextValue == "Запуск ОКР аппаратов")
                startRow = row;
            else if (currentRowTextValue == "Запуск серийных аппаратов")
                startRow = row - 1;
            else if (currentRowTextValue == "Блок КА")
                startRow = row - 2;
            else if (currentRowTextValue == "Ракета-носитель")
            {
                startRow = row - 3;
                brChanged = true;
            }
            qDebug() << startRow;
            for (int i=startRow;i<startRow+3;i++)
            {
                QVector <int> tmp;
                for (int j=1;j<ui->tableWidget_8->columnCount();j++)
                    tmp.append(ui->tableWidget_8->item(i,j)->text().toInt());
                yearsValues.append(tmp);
            }
            qDebug() <<yearsValues;
            for (int i=1;i<ui->tableWidget_8->columnCount();i++)
                boosterRocketValues.append(qobject_cast <QComboBox*> (ui->tableWidget_8->cellWidget(startRow+3,i))->currentText());
            QString projectName = ui->tableWidget_8->item(startRow-1,0)->text();
            QVector<QVector<QPair<QString,QString>>> valuesVector = tabPredictionModel.predictPrices(projectName,yearsValues,boosterRocketValues, brChanged, column-1);
            predictionTableEditedByUser = false;
            for (int i=0;i<valuesVector.length()-2;i++)
                for(int j=1;j<ui->tableWidget_8->columnCount();j++)
                {
                    if (valuesVector[i][j-1].first!="0") ui->tableWidget_8->item(startRow+i,j)->setText(valuesVector[i][j-1].first);
                    else ui->tableWidget_8->item(startRow+i,j)->setText("");
                    //ui->tableWidget_8->item(startRow+i,j)->setText(valuesVector[i][j-1].first);
                    if (valuesVector[i][j-1].second == "normal")
                        ui->tableWidget_8->item(startRow+i,j)->setBackgroundColor(QColor(255,255,255));
                    if (valuesVector[i][j-1].second == "current")
                        ui->tableWidget_8->item(startRow+i,j)->setBackgroundColor(QColor(244,255,244));
                    if (valuesVector[i][j-1].second == "expected")
                        ui->tableWidget_8->item(startRow+i,j)->setBackgroundColor(QColor(255,244,244));
                }
            for (int i=valuesVector.length()-3;i<valuesVector.length();i++)
                for(int j=1;j<ui->tableWidget_8->columnCount();j++)
                {
                    if (valuesVector[i][j-1].first!="0") ui->tableWidget_8->item(startRow+i,j)->setText(valuesVector[i][j-1].first);
                    else ui->tableWidget_8->item(startRow+i,j)->setText("");
                }


            QVector<qreal> spaceCraftTotal, boosterRocketTotal, total;
            for (int i=0;i<ui->tableWidget_8->columnCount();i++)
            {
                spaceCraftTotal.append(0);
                boosterRocketTotal.append(0);
                total.append(0);
            }
            for (int i=0; i<ui->tableWidget_8->rowCount();i++)
            {
                if (ui->tableWidget_8->item(i,0)->text()=="Цены КА ОКР+Серия")
                    for (int j=1;j<ui->tableWidget_8->columnCount();j++)
                        spaceCraftTotal[j-1] += ui->tableWidget_8->item(i,j)->text().toDouble();
                if (ui->tableWidget_8->item(i,0)->text()=="Цены РН проекта")
                    for (int j=1;j<ui->tableWidget_8->columnCount();j++)
                        boosterRocketTotal[j-1] += ui->tableWidget_8->item(i,j)->text().toDouble();
            }
            for (int i=1;i<spaceCraftTotal.length();i++)
            {
                if (spaceCraftTotal[i-1] == 0)
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-3,i)->setText("");
                else
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-3,i)->setText(QString::number(spaceCraftTotal[i-1]));
                if (boosterRocketTotal[i-1] == 0)
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-2,i)->setText("");
                else
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-2,i)->setText(QString::number(boosterRocketTotal[i-1]));
                total[i-1] += (spaceCraftTotal[i-1]+boosterRocketTotal[i-1]);
                if (total[i-1] == 0)
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-1,i)->setText("");
                else
                    ui->tableWidget_8->item(ui->tableWidget_8->rowCount()-1,i)->setText(QString::number(total[i-1]));
            }

            predictionTableEditedByUser = true;

            qDebug() << yearsValues << boosterRocketValues;
        }
        else
        {
            ui->tableWidget_8->item(row,column)->setText("");
        }
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    QString boosterRocketName = ui->comboBox_6->currentText();
    QString upperBlockName = ui->comboBox_7->currentText();
    QString spaceportName = ui->comboBox_8->currentText();
    int priceYear = ui->spinBox_2->value();
    QString prices = "";
    for (int i=1;i<ui->tableWidget_9->columnCount();i++)
    {
        prices += ui->tableWidget_9->item(0,i)->text() + ";";
    }
    qreal launchPrice = ui->doubleSpinBox_2->value();
    qreal deliveryPrice = ui->doubleSpinBox->value();
    qreal minPayload = ui->doubleSpinBox_3->value();
    qreal maxPayload = ui->doubleSpinBox_4->value();
    model.updateLaunchPricesByIds(boosterRocketName, upperBlockName, spaceportName, priceYear, prices, launchPrice, deliveryPrice, minPayload, maxPayload);
}

void MainWindow::on_pushButton_13_clicked()
{

}




