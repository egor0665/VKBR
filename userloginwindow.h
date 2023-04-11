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

    void closeEvent(QCloseEvent *);
Q_SIGNALS:
    void login(QString login, QString password);
    void closeApp();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userLoginWindow *ui;
};

#endif // USERLOGINWINDOW_H
