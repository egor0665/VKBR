#include "upper_block.h"

Upper_block::Upper_block()
{

}

Upper_block::Upper_block(int id, const QString &phys_info, const QString &econ_indo) : _id(id),
    _phys_info(phys_info),
    _econ_info(econ_indo)
{}

int Upper_block::id() const
{
    return _id;
}

void Upper_block::setId(int newId)
{
    _id = newId;
}

const QString &Upper_block::phys_info() const
{
    return _phys_info;
}

void Upper_block::setPhys_info(const QString &newPhys_info)
{
    _phys_info = newPhys_info;
}

const QString &Upper_block::econ_info() const
{
    return _econ_info;
}

void Upper_block::setEcon_info(const QString &newEcon_indo)
{
    _econ_info = newEcon_indo;
}

QStringList Upper_block::getValues()
{
    QStringList values;

    values.append(this->phys_info());
    values.append(this->econ_info());

    return values;
}
