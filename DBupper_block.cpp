#include "DBupper_block.h"

DBUpper_block::DBUpper_block()
{

}

DBUpper_block::DBUpper_block(int id, const QString &phys_info, const QString &econ_indo) : _id(id),
    _phys_info(phys_info),
    _econ_info(econ_indo)
{}

int DBUpper_block::id() const
{
    return _id;
}

void DBUpper_block::setId(int newId)
{
    _id = newId;
}

const QString &DBUpper_block::phys_info() const
{
    return _phys_info;
}

void DBUpper_block::setPhys_info(const QString &newPhys_info)
{
    _phys_info = newPhys_info;
}

const QString &DBUpper_block::econ_info() const
{
    return _econ_info;
}

void DBUpper_block::setEcon_info(const QString &newEcon_indo)
{
    _econ_info = newEcon_indo;
}

QStringList DBUpper_block::getValues()
{
    QStringList values;

    values.append(this->phys_info());
    values.append(this->econ_info());

    return values;
}
