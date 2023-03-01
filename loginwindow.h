#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class databaseloginwindow;
}

class databaseloginwindow : public QDialog
{
    Q_OBJECT

public:
    explicit databaseloginwindow(QWidget *parent = nullptr);
    ~databaseloginwindow();
public slots:
    void reject();
private:
    Ui::databaseloginwindow *ui;
};

#endif // LOGINWINDOW_H
