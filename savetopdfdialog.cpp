#include "savetopdfdialog.h"
#include "ui_savetopdfdialog.h"

SaveToPdfDialog::SaveToPdfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveToPdfDialog)
{
    ui->setupUi(this);
    ui->listWidget->addItems({"Строка Направление",
                              "Аппараты Связь",
                              "Аппараты ДЗЗ",
                              "Аппараты ФКИ",
                              "Аппараты Другое",
                              "Строка Запуск ОКР аппаратов",
                              "Строка Запуск серийных аппаратов",
                              "Строка Блок КА",
                              "Строка Ракета-носитель",
                              "Строка Цены КА ОКР+Серия",
                              "Строка Цены РН проекта",
                              "Строка Цены КА",
                              "Строка Цены РН",
                              "Строка Итого",
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
    if (item->text()=="Строка Направление")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount);
        else
            ui->tableWidget->hideRow(rowCount);
    }
    else if (item->text()=="Аппараты Связь")
    {

    }
    else if (item->text()=="Аппараты ДЗЗ")
    {

    }
    else if (item->text()=="Аппараты ФКИ")
    {

    }
    else if (item->text()=="Аппараты Другое")
    {

    }
    else if (item->text()=="Строка Название")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+1);
        else
            ui->tableWidget->hideRow(rowCount+1);
    }
    else if (item->text()=="Строка Запуск ОКР аппаратов")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+2);
        else
            ui->tableWidget->hideRow(rowCount+2);
    }
    else if (item->text()=="Строка Запуск серийных аппаратов")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+3);
        else
            ui->tableWidget->hideRow(rowCount+3);
    }
    else if (item->text()=="Строка Блок КА")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+4);
        else
            ui->tableWidget->hideRow(rowCount+4);
    }
    else if (item->text()=="Строка Ракета-носитель")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+5);
        else
            ui->tableWidget->hideRow(rowCount+5);
    }
    else if (item->text()=="Строка Цены КА ОКР+Серия")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+6);
        else
            ui->tableWidget->hideRow(rowCount+6);
    }
    else if (item->text()=="Строка Цены РН проекта")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+7);
        else
            ui->tableWidget->hideRow(rowCount+7);
    }
    else if (item->text()=="Строка Цены КА")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+8);
        else
            ui->tableWidget->hideRow(rowCount+8);
    }
    else if (item->text()=="Строка Цены РН")
    {
        if(item->checkState()==Qt::Checked)
            ui->tableWidget->showRow(rowCount+9);
        else
            ui->tableWidget->hideRow(rowCount+9);
    }
    else if (item->text()=="Строка Итого")
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
    for(int i=0;i<ui->listWidget->count();i++)
    {
        if (ui->listWidget->item(i)->checkState()==Qt::Checked)
            values.append(ui->listWidget->item(i)->text());
    }
    emit startSave(values, ui->spinBox->value(), ui->spinBox_2->value());
}

//void SaveToPdfDialog::startSave(QVector<QString> values, int startYear, int endYear)
//{

//}

