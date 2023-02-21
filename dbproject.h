#ifndef DBPROJECT_H
#define DBPROJECT_H

#include <qstring.h>



class DBProject
{
public:
    DBProject();
    DBProject(int id, const QString &name, const QString &type, int unit_id, const QString &first_unit_prices, const QString &last_unit_prices, const QString &pre_prices, const QString &post_prices, const QString &serial_prices);

    int id() const;
    const QString &name() const;
    const QString &type() const;
    int unit_id() const;

    const QString &pre_prices() const;
    const QString &post_prices() const;

    const QString &serial_prices() const;

    const QString &first_unit_prices() const;
    const QString &last_unit_prices() const;

private:
    int _id;
    QString _name;
    QString _type;
    int _unit_id;
    QString _first_unit_prices;
    QString _last_unit_prices;
    QString _pre_prices;
    QString _post_prices;
    QString _serial_prices;
//    QVector <qreal> _unit_prices();
//    QVector <qreal> _pre_prices();
//    QVector <qreal> _post_prices();
};

#endif // DBPROJECT_H
