#include "chartwidget.h"
#include "ui_chartwidget.h"

chartWidget::chartWidget(QWidget *parent, QPolarChart *chart) :
    QWidget(parent),
    ui(new Ui::chartWidget)
{
    ui->setupUi(this);
    ui->widget->setChart(chart);
}

chartWidget::~chartWidget()
{
    delete ui;
}
