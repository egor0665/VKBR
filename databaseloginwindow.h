#ifndef DATABASELOGINWINDOW_H
#define DATABASELOGINWINDOW_H

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

#endif // DATABASELOGINWINDOW_H
