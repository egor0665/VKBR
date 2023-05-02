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

void DBProject::setId(int newId)
{
    _id = newId;
}

void DBProject::setName(const QString &newName)
{
    _name = newName;
}

void DBProject::setType(const QString &newType)
{
    _type = newType;
}

void DBProject::setUnit_id(int newUnit_id)
{
    _unit_id = newUnit_id;
}

void DBProject::setFirst_unit_prices(const QString &newFirst_unit_prices)
{
    _first_unit_prices = newFirst_unit_prices;
}

void DBProject::setLast_unit_prices(const QString &newLast_unit_prices)
{
    _last_unit_prices = newLast_unit_prices;
}

void DBProject::setPre_prices(const QString &newPre_prices)
{
    _pre_prices = newPre_prices;
}

void DBProject::setPost_prices(const QString &newPost_prices)
{
    _post_prices = newPost_prices;
}

void DBProject::setSerial_prices(const QString &newSerial_prices)
{
    _serial_prices = newSerial_prices;
}




