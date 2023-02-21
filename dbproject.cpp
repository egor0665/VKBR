#include "dbproject.h"

DBProject::DBProject()
{

}

DBProject::DBProject(int id, const QString &name, const QString &type, int unit_id, const QString &pre_prices, const QString &first_unit_prices, const QString &last_unit_prices, const QString &post_prices, const QString &serial_prices) : _id(id),
    _name(name),
    _type(type),
    _unit_id(unit_id),
    _first_unit_prices(first_unit_prices),
    _last_unit_prices(last_unit_prices),
    _pre_prices(pre_prices),
    _post_prices(post_prices),
    _serial_prices(serial_prices)
{}

int DBProject::id() const
{
    return _id;
}

const QString &DBProject::name() const
{
    return _name;
}

const QString &DBProject::type() const
{
    return _type;
}

int DBProject::unit_id() const
{
    return _unit_id;
}


const QString &DBProject::pre_prices() const
{
    return _pre_prices;
}

const QString &DBProject::post_prices() const
{
    return _post_prices;
}

const QString &DBProject::serial_prices() const
{
    return _serial_prices;
}

const QString &DBProject::first_unit_prices() const
{
    return _first_unit_prices;
}

const QString &DBProject::last_unit_prices() const
{
    return _last_unit_prices;
}




