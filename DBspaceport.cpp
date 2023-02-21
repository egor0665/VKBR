#include "DBspaceport.h"

DBSpaceport::DBSpaceport()
{

}

int DBSpaceport::id() const
{
    return _id;
}

void DBSpaceport::setId(int newId)
{
    _id = newId;
}

const QString &DBSpaceport::name() const
{
    return _name;
}

void DBSpaceport::setName(const QString &newName)
{
    _name = newName;
}

DBSpaceport::DBSpaceport(int id, const QString &name) : _id(id),
    _name(name)
{}
