#ifndef DBUPPER_BLOCK_H
#define DBUPPER_BLOCK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class DBUpper_block
{
public:

    const int UPPER_BLOCK_DEF_ROW_NUM = 2;
    const QStringList UPPER_BLOCK_VALUES = {"phys_info", "econ_info"};

    DBUpper_block();
    DBUpper_block(int id, const QString &phys_info, const QString &econ_indo);

    QStringList getValues();

    int id() const;
    void setId(int newId);
    const QString &phys_info() const;
    void setPhys_info(const QString &newPhys_info);
    const QString &econ_info() const;
    void setEcon_info(const QString &newEcon_indo);

private:
    int _id;
    QString _phys_info;
    QString _econ_info;

};

#endif // DBUPPER_BLOCK_H
