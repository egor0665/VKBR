#include "userloginwindow.h"
#include "ui_userloginwindow.h"

userLoginWindow::userLoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userLoginWindow)
{
    ui->setupUi(this);
}

userLoginWindow::~userLoginWindow()
{
    delete ui;
}
