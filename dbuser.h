#ifndef DBUSER_H
#define DBUSER_H

#include <QString>



class DBUser
{
public:
    DBUser();
    DBUser(int id, const QString &name, const QString &role, const QString &password);



    int id() const;
    void setId(int newId);
    const QString &name() const;
    void setName(const QString &newName);
    const QString &role() const;
    void setRole(const QString &newRole);
    const QString &password() const;
    void setPassword(const QString &newPassword);

private:
    int _id;
    QString _name;
    QString _role;
    QString _password;
};

#endif // DBUSER_H
