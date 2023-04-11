#include "DBspacecraft.h"

DBSpacecraft::DBSpacecraft()
{

}

DBSpacecraft::DBSpacecraft(int id, qreal weight, qreal active_lifetime, const QString &phys_info, const QString &econ_info) : _id(id),
    _weight(std::move(weight)),
    _active_lifetime(std::move(active_lifetime)),
    _phys_info(phys_info),
    _econ_info(econ_info)
{}


int DBSpacecraft::id() const
{
    return _id;
}

const QString &DBSpacecraft::phys_info() const
{
    return _phys_info;
}

const QString &DBSpacecraft::econ_info() const
{
    return _econ_info;
}

qreal DBSpacecraft::active_lifetime() const
{
    return _active_lifetime;
}

qreal DBSpacecraft::weight() const
{
    return _weight;
}

QStringList DBSpacecraft::getValues()
{
    QStringList values;

    values.append(QString::number(this->weight()));
    values.append(QString::number(this->active_lifetime()));
    values.append(this->econ_info());
    values.append(this->phys_info());

    return values;
}

