#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseloginwindow.h"
#include <QVariant>
#include <QDebug>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startUI();
    databaseloginwindow *loginwindow = new databaseloginwindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startUI(){ 
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->setColumnCount(1);
    model.createNavigationTree(treeItem);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    tab2Init();
}

void MainWindow::tab2Init()
{
     QStringList names = db.getUnitNames();
     ui->comboBox->addItems(names);
     ui->comboBox_2->addItems(names);
     ui->tableWidget_4->verticalHeader()->hide();

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

    int rowCount = ui->tableWidget->rowCount();

    int unitId = model.getUnitIdByName(item->text(0));
    QVector<QPair<QString,QString>> values = model.getUnitData(unitId);
    for (int i=0;i<values.length(); i++){
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount,1, new QTableWidgetItem(values[i].first));
        ui->tableWidget->setItem(rowCount,2, new QTableWidgetItem(values[i].second));
        rowCount++;
    }

    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(3); // Указываем число колонок
    ui->tableWidget_2->setShowGrid(true); // Включаем сетку
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_2->setHorizontalHeaderLabels({"Номер показателя", "Параметр", "Значение"});
    ui->tableWidget_2->hideColumn(0);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    rowCount = ui->tableWidget_2->rowCount();

    values = model.getUnitEconData(unitId);
    for (int i=0;i<values.length(); i++){
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount,1, new QTableWidgetItem(values[i].first));
        ui->tableWidget->setItem(rowCount,2, new QTableWidgetItem(values[i].second));
        rowCount++;
    }
    ui->label_3->setText(item->text(0));


    //---------------------
    QImage picture = QImage(model.getUnitImageFromId(unitId));
    ui->label->setPixmap(QPixmap::fromImage(picture));
    picture = QImage("C:\\Catalog\\Scheme");
    ui->label_6->setPixmap(QPixmap::fromImage(picture));
    //---------------------
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

    int unitId_1 = model.getUnitIdByName(unitName1);
    int unitId_2 = model.getUnitIdByName(unitName2);
    QVector<QPair<QString,QString>> values_1 = model.getUnitData(unitId_1);
    QVector<QPair<QString,QString>> values_2 = model.getUnitData(unitId_2);
    QVector<QPair<QString,QStringList>> compareVector = model.formCompareTable(values_1, values_2);
    int rowCount = 0;
    for (int i=0;i<compareVector.length(); i++){
            ui->tableWidget_4->insertRow(rowCount);
            ui->tableWidget_4->setItem(rowCount,0, new QTableWidgetItem(compareVector[i].first));
            ui->tableWidget_4->setItem(rowCount,1, new QTableWidgetItem(compareVector[i].second[0]));
            ui->tableWidget_4->setItem(rowCount,2, new QTableWidgetItem(compareVector[i].second[1]));
            rowCount++;
    }

    QImage picture = QImage(model.getUnitImageFromId(unitId_1));
    ui->label_7->setPixmap(QPixmap::fromImage(picture).scaled(ui->comboBox->width(),ui->comboBox->width(),Qt::KeepAspectRatio));
    picture = QImage(model.getUnitImageFromId(unitId_2));
    ui->label_8->setPixmap(QPixmap::fromImage(picture).scaled(ui->comboBox->width(),ui->comboBox->width(),Qt::KeepAspectRatio));

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setColumnWidth(1,ui->tableWidget_4->width()/2);
}
