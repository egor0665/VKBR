#include "chartdialog.h"
#include "ui_chartdialog.h"

chartDialog::chartDialog(QWidget *parent, QPolarChart *chart) :
    QDialog(parent),
    ui(new Ui::chartDialog)
{
    ui->setupUi(this);
    ui->widget->setChart(chart);
}

chartDialog::~chartDialog()
{
    delete ui;
}
