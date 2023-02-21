#include "DBspacecraft.h"

DBSpacecraft::DBSpacecraft()
{

}

DBSpacecraft::DBSpacecraft(int id, int weight, const QString &phys_info, const QString &econ_info) : _id(id),
    _weight(weight),
    _phys_info(phys_info),
    _econ_info(econ_info)
{}

int DBSpacecraft::id() const
{
    return _id;
}

int DBSpacecraft::weight() const
{
    return _weight;
}

const QString &DBSpacecraft::phys_info() const
{
    return _phys_info;
}

const QString &DBSpacecraft::econ_info() const
{
    return _econ_info;
}
