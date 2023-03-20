#ifndef DBSPACECRAFT_H
#define DBSPACECRAFT_H

#include <qstringlist.h>



class DBSpacecraft
{

public:
    const int SPACECRAFT_DEF_ROW_NUM = 4;
    const QStringList BOOSTER_ROCKET_VALUES = {"Вес", "САС", "phys_info", "econ_info"};
    DBSpacecraft();
    DBSpacecraft(int id, qreal weight, qreal active_lifetime, const QString &phys_info, const QString &econ_info);


    int id() const;

    const QString &phys_info() const;
    const QString &econ_info() const;

    qreal active_lifetime() const;

    qreal weight() const;

private:
int _id;
qreal _weight;
qreal _active_lifetime;
QString _phys_info;
QString _econ_info;
};


#endif // DBSPACECRAFT_H
