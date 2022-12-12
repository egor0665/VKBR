#include "organization.h"

Organization::Organization()
{

}

int Organization::id() const
{
    return _id;
}

void Organization::setId(int newId)
{
    _id = newId;
}

const QString &Organization::name() const
{
    return _name;
}

void Organization::setName(const QString &newName)
{
    _name = newName;
}

Organization::Organization(int id, const QString &name) : _id(id),
    _name(name)
{}
