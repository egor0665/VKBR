#ifndef USERLOGINWINDOW_H
#define USERLOGINWINDOW_H

#include <QDialog>

namespace Ui {
class userLoginWindow;
}

class userLoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userLoginWindow(QWidget *parent = nullptr);
    ~userLoginWindow();

private:
    Ui::userLoginWindow *ui;
};

#endif // USERLOGINWINDOW_H
