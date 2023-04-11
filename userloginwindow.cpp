#include "userloginwindow.h"
#include "ui_userloginwindow.h"

userLoginWindow::userLoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userLoginWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

userLoginWindow::~userLoginWindow()
{
    delete ui;
}

void userLoginWindow::on_pushButton_2_clicked()
{
    login(ui->lineEdit->text(),ui->lineEdit_2->text());
    ui->lineEdit_2->setText("");
}

void userLoginWindow::on_pushButton_clicked()
{
    closeApp();
    ui->lineEdit_2->setText("");
}

void userLoginWindow::closeEvent(QCloseEvent *)
{
    closeApp();
}

