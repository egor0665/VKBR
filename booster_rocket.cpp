#include "booster_rocket.h"

Booster_rocket::Booster_rocket()
{

}

Booster_rocket::Booster_rocket(int id, const QString &load_class, int stages_num, const QString &fuel_type, const QString &phys_info) : _id(id),
    _load_class(load_class),
    _stages_num(stages_num),
    _fuel_type(fuel_type),
    _phys_info(phys_info)
{}

int Booster_rocket::id() const
{
    return _id;
}

void Booster_rocket::setId(int newId)
{
    _id = newId;
}

const QString &Booster_rocket::load_class() const
{
    return _load_class;
}

void Booster_rocket::setLoad_class(const QString &newLoad_class)
{
    _load_class = newLoad_class;
}

int Booster_rocket::stages_num() const
{
    return _stages_num;
}

void Booster_rocket::setStages_num(int newStages_num)
{
    _stages_num = newStages_num;
}

const QString &Booster_rocket::fuel_type() const
{
    return _fuel_type;
}

void Booster_rocket::setFuel_type(const QString &newFuel_type)
{
    _fuel_type = newFuel_type;
}

const QString &Booster_rocket::phys_info() const
{
    return _phys_info;
}

void Booster_rocket::setPhys_info(const QString &newPhys_info)
{
    _phys_info = newPhys_info;
}

const QString &Booster_rocket::econ_info() const
{
    return _econ_info;
}

void Booster_rocket::setEcon_info(const QString &newEcon_info)
{
    _econ_info = newEcon_info;
}

QStringList Booster_rocket::getValues()
{
    QStringList values;

    values.append(this->load_class());
    values.append(QString::number(this->stages_num()));
    values.append(this->fuel_type());
    values.append(this->phys_info());
    values.append(this->econ_info());

    return values;
}
