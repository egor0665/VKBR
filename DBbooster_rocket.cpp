#include "DBbooster_rocket.h"

DBBooster_rocket::DBBooster_rocket()
{

}


QStringList DBBooster_rocket::getValues()
{
    QStringList values;

    values.append(QString::number(this->max_payload()));
    values.append(QString::number(this->min_payload()));
    values.append(this->phys_info());
    values.append(this->econ_info());

    return values;
}

int DBBooster_rocket::id() const
{
    return _id;
}

const QString &DBBooster_rocket::phys_info() const
{
    return _phys_info;
}

const QString &DBBooster_rocket::econ_info() const
{
    return _econ_info;
}

int DBBooster_rocket::max_payload() const
{
    return _max_payload;
}

int DBBooster_rocket::min_payload() const
{
    return _min_payload;
}

void DBBooster_rocket::setId(int newId)
{
    _id = newId;
}

void DBBooster_rocket::setMax_payload(int newMax_payload)
{
    _max_payload = newMax_payload;
}

void DBBooster_rocket::setMin_payload(int newMin_payload)
{
    _min_payload = newMin_payload;
}

void DBBooster_rocket::setPhys_info(const QString &newPhys_info)
{
    _phys_info = newPhys_info;
}

void DBBooster_rocket::setEcon_info(const QString &newEcon_info)
{
    _econ_info = newEcon_info;
}

DBBooster_rocket::DBBooster_rocket(int id, int max_payload, int min_payload, const QString &phys_info, const QString &econ_info) : _id(id),
    _max_payload(max_payload),
    _min_payload(min_payload),
    _phys_info(phys_info),
    _econ_info(econ_info)
{}
