#include "dbuser.h"

DBUser::DBUser()
{

}

int DBUser::id() const
{
    return _id;
}

void DBUser::setId(int newId)
{
    _id = newId;
}

const QString &DBUser::name() const
{
    return _name;
}

void DBUser::setName(const QString &newName)
{
    _name = newName;
}

const QString &DBUser::role() const
{
    return _role;
}

void DBUser::setRole(const QString &newRole)
{
    _role = newRole;
}

const QString &DBUser::password() const
{
    return _password;
}

void DBUser::setPassword(const QString &newPassword)
{
    _password = newPassword;
}

DBUser::DBUser(int id, const QString &name, const QString &role, const QString &password) : _id(id),
    _name(name),
    _role(role),
    _password(password)
{}
