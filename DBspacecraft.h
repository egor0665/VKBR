#ifndef DBSPACECRAFT_H
#define DBSPACECRAFT_H

#include <qstringlist.h>



class DBSpacecraft
{

public:
    const int SPACECRAFT_DEF_ROW_NUM = 3;
    const QStringList BOOSTER_ROCKET_VALUES = {"Вес", "phys_info", "econ_info"};
    DBSpacecraft();
    DBSpacecraft(int id, int weight, const QString &phys_info, const QString &econ_info);

    int id() const;
    int weight() const;
    const QString &phys_info() const;
    const QString &econ_info() const;

private:
int _id;
int _weight;
QString _phys_info;
QString _econ_info;
};


#endif // DBSPACECRAFT_H
