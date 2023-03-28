#include "savetopdfdialog.h"
#include "ui_savetopdfdialog.h"

SaveToPdfDialog::SaveToPdfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveToPdfDialog)
{
    ui->setupUi(this);
    ui->listWidget->addItems({"Направление",
                              "Связь",
                              "ДЗЗ",
                              "ФКИ",
                              "Другое",
                              "Запуск ОКР аппаратов",
                              "Запуск серийных аппаратов",
                              "Блок КА",
                              "Ракета-носитель",
                              "Цены КА ОКР+Серия",
                              "Цены РН проекта",
                              "Цены КА",
                              "Цены РН",
                              "Итого",
                              });
    for(int i=0;i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setFlags(ui->listWidget->item(i)->flags() | Qt::ItemIsUserCheckable);
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setColumnCount(2); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setHorizontalHeaderLabels({"","2024"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //QVector<QVector<qreal>> prices = model.getProjectPricesFromName(arg1);

    int rowCount = ui->tableWidget->rowCount();
    for (int i=0;i<11;i++)
    {
        ui->tableWidget->insertRow(rowCount+i);
    }

    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem("Направление"));
    ui->tableWidget->setItem(rowCount+1, 0, new QTableWidgetItem("Название"));
    ui->tableWidget->setItem(rowCount+2, 0, new QTableWidgetItem("Запуск ОКР аппаратов"));
    ui->tableWidget->setItem(rowCount+3, 0, new QTableWidgetItem("Запуск серийных аппаратов"));
    ui->tableWidget->setItem(rowCount+4, 0, new QTableWidgetItem("Блок КА"));
    ui->tableWidget->setItem(rowCount+5, 0, new QTableWidgetItem("Ракета-носитель"));
    ui->tableWidget->setItem(rowCount+6, 0, new QTableWidgetItem("Цены КА ОКР+Серия"));

    ui->tableWidget->setItem(rowCount+7, 0, new QTableWidgetItem("Цены РН проект"));
    ui->tableWidget->setItem(rowCount+8, 0, new QTableWidgetItem("Цены КА"));
    ui->tableWidget->setItem(rowCount+9, 0, new QTableWidgetItem("Цены РН"));
    ui->tableWidget->setItem(rowCount+10, 0, new QTableWidgetItem("Итого"));

    ui->tableWidget->item(rowCount, 0)->setBackgroundColor(QColor(255,239,214));
    ui->tableWidget->item(rowCount+1, 0)->setBackgroundColor(QColor(255,245,224));

    //ui->tableWidget->item(rowCount+9, 0)->setBackgroundColor(QColor(244,244,255));
    ui->tableWidget->item(rowCount+6, 0)->setBackgroundColor(QColor(244,244,255));
    ui->tableWidget->item(rowCount+7, 0)->setBackgroundColor(QColor(244,244,255));
    ui->tableWidget->item(rowCount+8, 0)->setBackgroundColor(QColor(244,244,255));
    ui->tableWidget->item(rowCount+9, 0)->setBackgroundColor(QColor(244,244,255));
    ui->tableWidget->item(rowCount+10, 0)->setBackgroundColor(QColor(244,244,255));
}

SaveToPdfDialog::~SaveToPdfDialog()
{
    delete ui;
}

void SaveToPdfDialog::on_listWidget_itemChanged(QListWidgetItem *item)
{
    int rowCount=0;
    if (item->text()=="Направление")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount);
        else
            ui->tableWidget->hideRow(rowCount);
    }
    else if (item->text()=="Связь")
    {

    }
    else if (item->text()=="ДЗЗ")
    {

    }
    else if (item->text()=="ФКИ")
    {

    }
    else if (item->text()=="Другое")
    {

    }
    else if (item->text()=="Название")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+1);
        else
            ui->tableWidget->hideRow(rowCount+1);
    }
    else if (item->text()=="Запуск ОКР аппаратов")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+2);
        else
            ui->tableWidget->hideRow(rowCount+2);
    }
    else if (item->text()=="Запуск серийных аппаратов")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+3);
        else
            ui->tableWidget->hideRow(rowCount+3);
    }
    else if (item->text()=="Блок КА")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+4);
        else
            ui->tableWidget->hideRow(rowCount+4);
    }
    else if (item->text()=="Ракета-носитель")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+5);
        else
            ui->tableWidget->hideRow(rowCount+5);
    }
    else if (item->text()=="Цены КА ОКР+Серия")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+6);
        else
            ui->tableWidget->hideRow(rowCount+6);
    }
    else if (item->text()=="Цены РН проекта")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+7);
        else
            ui->tableWidget->hideRow(rowCount+7);
    }
    else if (item->text()=="Цены КА")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+8);
        else
            ui->tableWidget->hideRow(rowCount+8);
    }
    else if (item->text()=="Цены РН")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+9);
        else
            ui->tableWidget->hideRow(rowCount+9);
    }
    else if (item->text()=="Итого")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+10);
        else
            ui->tableWidget->hideRow(rowCount+10);
    }
}


void SaveToPdfDialog::on_pushButton_clicked()
{
    QVector<QString> values;
    QString name = ui->lineEdit->text();
    for(int i=0;i<ui->listWidget->count();i++)
    {
        if (ui->listWidget->item(i)->checkState()==Qt::Checked)
            values.append(ui->listWidget->item(i)->text());
    }
    emit startSave(name, values, ui->spinBox->value(), ui->spinBox_2->value());
}

//void SaveToPdfDialog::startSave(QVector<QString> values, int startYear, int endYear)
//{

//}

