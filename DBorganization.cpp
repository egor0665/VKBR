#include "DBorganization.h"

DBOrganization::DBOrganization()
{

}

int DBOrganization::id() const
{
    return _id;
}

void DBOrganization::setId(int newId)
{
    _id = newId;
}

const QString &DBOrganization::name() const
{
    return _name;
}

void DBOrganization::setName(const QString &newName)
{
    _name = newName;
}

DBOrganization::DBOrganization(int id, const QString &name) : _id(id),
    _name(name)
{}
