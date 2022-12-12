#include "databaseloginwindow.h"
#include "ui_databaseloginwindow.h"
#include <QCloseEvent>
#include <QMessageBox>

databaseloginwindow::databaseloginwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseloginwindow)
{
    ui->setupUi(this);
    this->setModal(true);
}

databaseloginwindow::~databaseloginwindow()
{
    delete ui;
}

void databaseloginwindow::reject()
{

    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    if (true) {
        resBtn = QMessageBox::question( this, "Каталог",
                                        tr("Вы уверены что хотите выйти?\n"),
                                        QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::Yes);
    }
    if (resBtn == QMessageBox::Yes) {
        QDialog::reject();
    }
}
