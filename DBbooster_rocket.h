#ifndef DBBOOSTER_ROCKET_H
#define DBBOOSTER_ROCKET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class DBBooster_rocket
{
public:
    const int BOOSTER_ROCKET_DEF_ROW_NUM = 4;
    const QStringList BOOSTER_ROCKET_VALUES = {"Максимальна грузоподъемность", "Минимальная грузоподъемность", "phys_info", "econ_info"};

    DBBooster_rocket();
    DBBooster_rocket(int id, int max_payload, int min_payload, const QString &phys_info, const QString &econ_info);


    QStringList getValues();

    int id() const;
    const QString &phys_info() const;
    const QString &econ_info() const;

    int max_payload() const;
    int min_payload() const;

private:
    int _id;
    int _max_payload;
    int _min_payload;
    QString _phys_info;
    QString _econ_info;

};

#endif // DBBOOSTER_ROCKET_H
