#include "spaceport.h"

Spaceport::Spaceport()
{

}

int Spaceport::id() const
{
    return _id;
}

void Spaceport::setId(int newId)
{
    _id = newId;
}

const QString &Spaceport::name() const
{
    return _name;
}

void Spaceport::setName(const QString &newName)
{
    _name = newName;
}

Spaceport::Spaceport(int id, const QString &name) : _id(id),
    _name(name)
{}
